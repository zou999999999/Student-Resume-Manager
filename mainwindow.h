#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QLineEdit>
#include <QTextEdit>

#include "model_layers.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    // 学业管理
    void onCalcGpaClicked();
    void onRemoveCourseClicked();

    // 履历素材库
    void onAddExperienceClicked();
    void onRemoveExperienceClicked();

    // 导出简历
    void onExportPdfClicked();

    // 标签页切换
    void onTabChanged(int index);

private:
    Ui::MainWindow    *ui;
    GpaLogic          *gpaTool;
    ResumeExporter    *exporter;

    QList<Course>      m_courses;
    QList<Experience>  m_experiences;
    double             m_currentGpa;

    // 内部辅助
    void refreshCourseTable();
    void refreshExperienceTable();
    void refreshExportSummary();
    ResumePackage assemblePackage() const;

    /// 解析手动输入的 "YYYY.MM" 日期字符串为 QDate（日默认为 1）
    static QDate parseDateText(const QString& text);
};

#endif // MAINWINDOW_H
