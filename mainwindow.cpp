#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QFileInfo>

// ============================================================================
// 构造 / 析构
// ============================================================================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gpaTool(new GpaLogic)
    , exporter(new ResumeExporter)
    , m_currentGpa(0.0)
{
    ui->setupUi(this);

    // ---- 学业管理 ----
    connect(ui->btn_calc_gpa,    &QPushButton::clicked,
            this,                &MainWindow::onCalcGpaClicked);
    connect(ui->btnRemoveCourse, &QPushButton::clicked,
            this,                &MainWindow::onRemoveCourseClicked);

    // ---- 履历素材库 ----
    connect(ui->btnAddExp,    &QPushButton::clicked,
            this,             &MainWindow::onAddExperienceClicked);
    connect(ui->btnRemoveExp, &QPushButton::clicked,
            this,             &MainWindow::onRemoveExperienceClicked);

    // ---- 导出简历 ----
    connect(ui->btn_export_pdf, &QPushButton::clicked,
            this,               &MainWindow::onExportPdfClicked);

    // ---- 标签页切换刷新摘要 ----
    connect(ui->tabWidget, &QTabWidget::currentChanged,
            this,          &MainWindow::onTabChanged);

    // 初始化课程表格列头
    ui->twCourses->setColumnCount(3);
    ui->twCourses->setHorizontalHeaderLabels({
        QStringLiteral("课程名称"), QStringLiteral("学分"), QStringLiteral("成绩")});
    ui->twCourses->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    // 初始化经历表格列头
    ui->twExperiences->setColumnCount(4);
    ui->twExperiences->setHorizontalHeaderLabels({
        QStringLiteral("类型"), QStringLiteral("标题"),
        QStringLiteral("机构"), QStringLiteral("时间")});
    ui->twExperiences->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete gpaTool;
    delete exporter;
    delete ui;
}

// ============================================================================
// 日期解析: "2024.02" → QDate(2024, 2, 1)
// ============================================================================

QDate MainWindow::parseDateText(const QString& text)
{
    QString t = text.trimmed();
    if (t.isEmpty()) return QDate();

    QStringList parts = t.split(QLatin1Char('.'));
    if (parts.size() >= 2) {
        int y = parts[0].toInt();
        int m = parts[1].toInt();
        if (y >= 1900 && y <= 2100 && m >= 1 && m <= 12)
            return QDate(y, m, 1);
    }
    return QDate(); // 无效
}

// ============================================================================
// 槽：学业管理 —— 添加课程 + 计算 GPA
// ============================================================================

void MainWindow::onCalcGpaClicked()
{
    QString name      = ui->edit_course_name->text().trimmed();
    QString creditStr = ui->edit_course_credit->text().trimmed();
    QString scoreStr  = ui->edit_course_score->text().trimmed();

    if (name.isEmpty()) {
        ui->label_status_msg->setText(QStringLiteral("[学业] 请输入课程名称"));
        return;
    }

    bool creditOk = false;
    double credit = creditStr.toDouble(&creditOk);
    if (!creditOk || credit < 0.0) {
        ui->label_status_msg->setText(QStringLiteral("[学业] 请输入有效的学分（>=0）"));
        return;
    }

    bool scoreOk = false;
    double score = scoreStr.toDouble(&scoreOk);
    if (!scoreOk || score < 0.0 || score > 100.0) {
        ui->label_status_msg->setText(QStringLiteral("[学业] 请输入有效成绩（0-100）"));
        return;
    }

    m_courses.append(Course(name, credit, score));
    refreshCourseTable();

    m_currentGpa = gpaTool->calculateGPA(m_courses);
    double gpa4 = m_currentGpa / 100.0 * 4.0;

    ui->label_gpa_result->setText(
        QStringLiteral("当前 GPA：%1 / 100（%2 / 4.0）| 共 %3 门课程")
            .arg(m_currentGpa, 0, 'f', 1)
            .arg(gpa4, 0, 'f', 2)
            .arg(m_courses.size()));

    ui->label_status_msg->setText(
        QStringLiteral("[学业] 已添加「%1」— GPA 已更新").arg(name));

    ui->edit_course_name->clear();
    ui->edit_course_credit->clear();
    ui->edit_course_score->clear();
    ui->edit_course_name->setFocus();
    refreshExportSummary();
}

// ============================================================================
// 槽：学业管理 —— 删除选中课程
// ============================================================================

void MainWindow::onRemoveCourseClicked()
{
    int row = ui->twCourses->currentRow();
    if (row < 0 || row >= m_courses.size()) {
        ui->label_status_msg->setText(QStringLiteral("[学业] 请先选中要删除的课程"));
        return;
    }
    QString name = m_courses.at(row).name;
    m_courses.removeAt(row);
    refreshCourseTable();
    m_currentGpa = gpaTool->calculateGPA(m_courses);

    double gpa4 = m_currentGpa / 100.0 * 4.0;
    ui->label_gpa_result->setText(
        QStringLiteral("当前 GPA：%1 / 100（%2 / 4.0）| 共 %3 门课程")
            .arg(m_currentGpa, 0, 'f', 1)
            .arg(gpa4, 0, 'f', 2)
            .arg(m_courses.size()));

    ui->label_status_msg->setText(
        QStringLiteral("[学业] 已删除「%1」").arg(name));
    refreshExportSummary();
}

// ============================================================================
// 槽：履历素材库 —— 添加经历（日期改为手动文本输入）
// ============================================================================

void MainWindow::onAddExperienceClicked()
{
    QString title = ui->leExpTitle->text().trimmed();
    if (title.isEmpty()) {
        ui->label_status_msg->setText(QStringLiteral("[履历] 请输入经历标题"));
        return;
    }

    ExperienceType type;
    switch (ui->cbExpType->currentIndex()) {
    case 0:  type = ExperienceType::Internship; break;
    case 1:  type = ExperienceType::Project;    break;
    case 2:  type = ExperienceType::Activity;   break;
    default: type = ExperienceType::Other;       break;
    }

    QString org  = ui->leExpOrg->text().trimmed();
    QString desc = ui->teExpDesc->toPlainText().trimmed();

    // 手动输入日期 "YYYY.MM"
    QDate s = parseDateText(ui->edit_start_date->text());
    QDate e = parseDateText(ui->edit_end_date->text());

    m_experiences.append(Experience(type, title, org, s, e, desc));
    refreshExperienceTable();

    ui->leExpTitle->clear();
    ui->leExpOrg->clear();
    ui->edit_start_date->clear();
    ui->edit_end_date->clear();
    ui->teExpDesc->clear();
    ui->leExpTitle->setFocus();

    ui->label_status_msg->setText(
        QStringLiteral("[履历] 已添加「%1」— 共 %2 条经历")
            .arg(title).arg(m_experiences.size()));
    refreshExportSummary();
}

// ============================================================================
// 槽：履历素材库 —— 删除选中经历
// ============================================================================

void MainWindow::onRemoveExperienceClicked()
{
    int row = ui->twExperiences->currentRow();
    if (row < 0 || row >= m_experiences.size()) {
        ui->label_status_msg->setText(QStringLiteral("[履历] 请先选中要删除的经历"));
        return;
    }
    QString title = m_experiences.at(row).title;
    m_experiences.removeAt(row);
    refreshExperienceTable();
    ui->label_status_msg->setText(
        QStringLiteral("[履历] 已删除「%1」").arg(title));
    refreshExportSummary();
}

// ============================================================================
// 槽：导出简历 —— 一键 PDF
// ============================================================================

void MainWindow::onExportPdfClicked()
{
    QString name = ui->edit_full_name->text().trimmed();
    if (name.isEmpty()) {
        ui->label_status_msg->setText(QStringLiteral("[导出] 请先填写姓名"));
        return;
    }

    if (m_courses.isEmpty() && m_experiences.isEmpty()) {
        QMessageBox::information(this, QStringLiteral("提示"),
            QStringLiteral("当前没有任何课程或经历，请先录入。"));
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(
        this,
        QStringLiteral("导出 PDF 简历"),
        QDir::homePath() + QStringLiteral("/%1_简历.pdf").arg(name),
        QStringLiteral("PDF 文件 (*.pdf)"));

    if (filePath.isEmpty()) return;

    if (!m_courses.isEmpty()) {
        m_currentGpa = gpaTool->calculateGPA(m_courses);
    }

    ResumePackage pkg = assemblePackage();

    bool ok = exporter->exportToPdf(pkg, filePath);

    if (ok) {
        ui->label_status_msg->setText(
            QStringLiteral("[导出] 成功！已保存至 %1").arg(filePath));
        QMessageBox::information(this, QStringLiteral("导出成功"),
            QStringLiteral("简历 PDF 已保存至：\n%1").arg(filePath));
    } else {
        ui->label_status_msg->setText(QStringLiteral("[导出] 失败，请检查路径权限"));
        QMessageBox::warning(this, QStringLiteral("导出失败"),
            QStringLiteral("无法写入文件。\n%1").arg(filePath));
    }
}

// ============================================================================
// 标签页切换
// ============================================================================

void MainWindow::onTabChanged(int index)
{
    Q_UNUSED(index)
    refreshExportSummary();
}

// ============================================================================
// 内部辅助：表格刷新
// ============================================================================

void MainWindow::refreshCourseTable()
{
    ui->twCourses->setRowCount(m_courses.size());
    for (int i = 0; i < m_courses.size(); ++i) {
        const auto& c = m_courses[i];
        ui->twCourses->setItem(i, 0, new QTableWidgetItem(c.name));
        ui->twCourses->setItem(i, 1, new QTableWidgetItem(
            QString::number(c.credit, 'f', 1)));
        ui->twCourses->setItem(i, 2, new QTableWidgetItem(
            QString::number(c.grade, 'f', 1)));
    }
}

void MainWindow::refreshExperienceTable()
{
    ui->twExperiences->setRowCount(m_experiences.size());
    for (int i = 0; i < m_experiences.size(); ++i) {
        const auto& e = m_experiences[i];
        ui->twExperiences->setItem(i, 0,
            new QTableWidgetItem(experienceTypeName(e.type)));
        ui->twExperiences->setItem(i, 1,
            new QTableWidgetItem(e.title));
        ui->twExperiences->setItem(i, 2,
            new QTableWidgetItem(e.organization));
        ui->twExperiences->setItem(i, 3,
            new QTableWidgetItem(e.dateRange()));
    }
}

void MainWindow::refreshExportSummary()
{
    double gpa4 = m_currentGpa / 100.0 * 4.0;
    ui->lblSummary->setText(
        QStringLiteral("已录入 %1 门课程 | %2 段经历 | GPA：%3/100（%4/4.0）")
            .arg(m_courses.size())
            .arg(m_experiences.size())
            .arg(m_courses.isEmpty()
                     ? QStringLiteral("--")
                     : QString::number(m_currentGpa, 'f', 1))
            .arg(m_courses.isEmpty()
                     ? QStringLiteral("--")
                     : QString::number(gpa4, 'f', 2)));
}

ResumePackage MainWindow::assemblePackage() const
{
    ResumePackage pkg;
    pkg.fullName   = ui->edit_full_name->text().trimmed();
    pkg.contact    = ui->edit_contact->text().trimmed();
    pkg.targetJob  = ui->edit_target_job->text().trimmed();
    pkg.skills     = ui->edit_skills->toPlainText().trimmed();
    pkg.finalGpa   = m_currentGpa;
    pkg.courses    = m_courses;
    pkg.experiences = m_experiences;
    return pkg;
}
