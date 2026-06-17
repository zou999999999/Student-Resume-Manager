#include "model_layers.h"

#include <QTextDocument>
#include <QPrinter>
#include <QPageSize>
#include <QPageLayout>
#include <QMarginsF>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QFont>

// ============================================================================
// Experience 成员函数
// ============================================================================

QString Experience::dateRange() const
{
    if (!startDate.isValid() && !endDate.isValid())
        return QString();

    auto fmt = [](const QDate& d) -> QString {
        if (!d.isValid()) return QString();
        return QStringLiteral("%1.%2")
            .arg(d.year())
            .arg(d.month(), 2, 10, QLatin1Char('0'));
    };

    QString s = fmt(startDate);
    QString e = fmt(endDate);

    if (s.isEmpty() && e.isEmpty()) return QString();
    if (s.isEmpty()) return e;
    if (e.isEmpty()) return s + QStringLiteral(" - 至今");
    return s + QStringLiteral(" - ") + e;
}


// ============================================================================
// GpaLogic 实现
// ============================================================================

double GpaLogic::calculateGPA(const QList<Course>& courseList)
{
    double totalCredits = 0.0;
    double weightedSum  = 0.0;

    for (const auto& c : courseList) {
        totalCredits += c.credit;
        weightedSum  += c.credit * c.grade;
    }

    if (totalCredits == 0.0)
        return 0.0;

    return weightedSum / totalCredits;
}

void GpaLogic::calculateDetail(const QList<Course>& courseList,
                               double& totalCredits,
                               double& weightedSum)
{
    totalCredits = 0.0;
    weightedSum  = 0.0;

    for (const auto& c : courseList) {
        totalCredits += c.credit;
        weightedSum  += c.credit * c.grade;
    }
}


// ============================================================================
// ResumeExporter 实现 — Qt 6
// ============================================================================

bool ResumeExporter::exportToPdf(const ResumePackage& package,
                                 const QString& savePath)
{
    // 1. 生成 HTML
    QString html = buildHtml(package);

    // 2. 确保目标目录存在
    QFileInfo fi(savePath);
    QDir dir = fi.absoluteDir();
    if (!dir.exists()) {
        dir.mkpath(QStringLiteral("."));
    }

    // 3. QTextDocument 渲染 HTML
    QTextDocument doc;
    doc.setHtml(html);
    doc.setPageSize(QSizeF(595, 842));  // A4 pt, 兼容所有 Qt 版本

    QFont defaultFont(QStringLiteral("微软雅黑"), 10);
    doc.setDefaultFont(defaultFont);

    // 4. QPrinter → PDF (Qt 6 API)
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(savePath);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    doc.print(&printer);

    // 5. 校验
    return QFile::exists(savePath);
}


// ============================================================================
// HTML 简历模板
// ============================================================================

QString ResumeExporter::buildHtml(const ResumePackage& pkg)
{
    auto css = QStringLiteral(R"(
<style>
  * { margin: 0; padding: 0; box-sizing: border-box; }
  body {
    font-family: "微软雅黑", "Microsoft YaHei", "SimSun", Arial, sans-serif;
    font-size: 14px; color: #333; line-height: 1.6; padding: 10px 0 10px 0;
  }
  .header { text-align: center; margin-bottom: 16px; }
  .name { font-size: 26px; font-weight: bold; letter-spacing: 2px; margin-bottom: 4px; }
  .contact { font-size: 13px; color: #666; }
  .job-target { font-size: 13px; color: #2a6496; margin-top: 2px; }
  .section { margin-bottom: 16px; }
  .section-title {
    font-size: 16px; font-weight: bold; border-bottom: 2px solid #2a6496;
    padding-bottom: 3px; margin-bottom: 8px; color: #2a6496;
  }
  .info-line { margin-bottom: 4px; }
  .info-line .label { font-weight: bold; display: inline-block; min-width: 80px; }
  table.course-table { width: 100%; border-collapse: collapse; margin-bottom: 8px; }
  table.course-table th, table.course-table td {
    border: 1px solid #ddd; padding: 4px 8px; text-align: center; font-size: 13px;
  }
  table.course-table th { background-color: #eef3f8; font-weight: bold; }
  .exp-item { margin-bottom: 10px; }
  .exp-header { overflow: hidden; }
  .exp-title { font-weight: bold; font-size: 15px; float: left; }
  .exp-org { float: left; margin-left: 8px; color: #555; }
  .exp-date { float: right; font-size: 13px; color: #888; }
  .exp-desc { clear: both; margin-top: 4px; font-size: 13px; color: #444; white-space: pre-wrap; }
  .gpa-highlight { font-weight: bold; color: #c0392b; font-size: 16px; }
  .skills-block { font-size: 13px; line-height: 1.8; white-space: pre-wrap; }
  .divider { border: none; border-top: 1px dashed #ccc; margin: 8px 0; }
</style>
)");

    // 头部
    QString header;
    header += QStringLiteral("<div class=\"header\">\n");
    header += QStringLiteral("  <div class=\"name\">%1</div>\n")
        .arg(pkg.fullName.isEmpty() ? QStringLiteral("未填写") : pkg.fullName.toHtmlEscaped());
    header += QStringLiteral("  <div class=\"contact\">%1</div>\n")
        .arg(pkg.contact.isEmpty() ? QString() : pkg.contact.toHtmlEscaped());
    if (!pkg.targetJob.isEmpty()) {
        header += QStringLiteral("  <div class=\"job-target\">求职意向：%1</div>\n")
            .arg(pkg.targetJob.toHtmlEscaped());
    }
    header += QStringLiteral("</div>\n");

    // 教育背景
    QString education;
    education += QStringLiteral("<div class=\"section\">\n");
    education += QStringLiteral("  <div class=\"section-title\">教育背景</div>\n");
    double gpa4 = pkg.finalGpa / 100.0 * 4.0;
    education += QStringLiteral("  <div class=\"info-line\">"
        "<span class=\"label\">综合 GPA：</span>"
        "<span class=\"gpa-highlight\">%1 / 100（%2 / 4.0）</span></div>\n")
        .arg(pkg.finalGpa, 0, 'f', 1)
        .arg(gpa4, 0, 'f', 2);
    if (!pkg.courses.isEmpty()) {
        education += QStringLiteral("  <table class=\"course-table\">\n");
        education += QStringLiteral("    <tr><th>课程名称</th><th>学分</th><th>成绩</th></tr>\n");
        for (const auto& c : pkg.courses) {
            education += QStringLiteral("    <tr><td>%1</td><td>%2</td><td>%3</td></tr>\n")
                .arg(c.name.toHtmlEscaped(),
                     QString::number(c.credit, 'f', 1),
                     QString::number(c.grade,  'f', 1));
        }
        education += QStringLiteral("  </table>\n");
    }
    education += QStringLiteral("</div>\n");

    // 经历（按类型分组）
    QList<ExperienceType> typeOrder = {
        ExperienceType::Internship,
        ExperienceType::Project,
        ExperienceType::Activity,
        ExperienceType::Other
    };

    QString expHtml;
    for (auto etype : typeOrder) {
        QList<Experience> group;
        for (const auto& e : pkg.experiences) {
            if (e.type == etype) group.append(e);
        }
        if (group.isEmpty()) continue;

        expHtml += QStringLiteral("<div class=\"section\">\n");
        expHtml += QStringLiteral("  <div class=\"section-title\">%1</div>\n")
            .arg(experienceTypeName(etype));

        for (int i = 0; i < group.size(); ++i) {
            const auto& e = group[i];
            expHtml += QStringLiteral("  <div class=\"exp-item\">\n");
            expHtml += QStringLiteral("    <div class=\"exp-header\">\n");
            expHtml += QStringLiteral("      <span class=\"exp-title\">%1</span>\n")
                .arg(e.title.toHtmlEscaped());
            expHtml += QStringLiteral("      <span class=\"exp-org\">%1</span>\n")
                .arg(e.organization.toHtmlEscaped());
            expHtml += QStringLiteral("      <span class=\"exp-date\">%1</span>\n")
                .arg(e.dateRange());
            expHtml += QStringLiteral("    </div>\n");
            if (!e.description.isEmpty()) {
                expHtml += QStringLiteral("    <div class=\"exp-desc\">%1</div>\n")
                    .arg(e.description.toHtmlEscaped());
            }
            expHtml += QStringLiteral("  </div>\n");
            if (i < group.size() - 1) {
                expHtml += QStringLiteral("  <hr class=\"divider\">\n");
            }
        }
        expHtml += QStringLiteral("</div>\n");
    }

    // 技能 / 证书
    QString skillsBlock;
    if (!pkg.skills.isEmpty()) {
        skillsBlock += QStringLiteral("<div class=\"section\">\n");
        skillsBlock += QStringLiteral("  <div class=\"section-title\">技能 / 证书</div>\n");
        skillsBlock += QStringLiteral("  <div class=\"skills-block\">%1</div>\n")
            .arg(pkg.skills);
        skillsBlock += QStringLiteral("</div>\n");
    }

    // 拼装
    QString html;
    html += QStringLiteral("<!DOCTYPE html>\n<html><head><meta charset=\"utf-8\">\n");
    html += QStringLiteral("<title>简历 - %1</title>\n")
        .arg(pkg.fullName.isEmpty() ? QStringLiteral("Resume") : pkg.fullName.toHtmlEscaped());
    html += css;
    html += QStringLiteral("</head>\n<body>\n");
    html += header;
    html += education;
    html += expHtml;
    html += skillsBlock;
    html += QStringLiteral("</body>\n</html>\n");

    return html;
}
