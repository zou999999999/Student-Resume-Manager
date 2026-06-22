/**
 * 自动化单元测试程序
 * 覆盖 GPA 计算、JSON 读写、PDF 导出等核心逻辑
 *
 * 编译（需要链接 Qt）：
 *   g++ -std=c++17 test_runner.cpp model_layers.cpp datamanager.cpp \
 *       -I<Qt/include> -L<Qt/lib> -lQt6Core -lQt6Gui -lQt6PrintSupport -fPIC
 *
 * 或在 Qt Creator 中作为独立子项目编译运行。
 */

#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>

#include "model_layers.h"
#include "datamanager.h"

// ============================================================================
// 测试辅助宏
// ============================================================================

static int g_passed = 0;
static int g_failed = 0;

#define TEST(name) \
    qDebug() << "\n========== TEST:" << name << "==========";

#define ASSERT_EQ(a, b, label) do { \
    auto _a = (a); auto _b = (b); \
    if (_a == _b) { qDebug() << "  [PASS]" << label; g_passed++; } \
    else { qDebug() << "  [FAIL]" << label << "- expected:" << _b << "got:" << _a; g_failed++; } \
} while(0)

#define ASSERT_TRUE(cond, label) \
    ASSERT_EQ((cond), true, label);

#define ASSERT_FALSE(cond, label) \
    ASSERT_EQ((cond), false, label);


// ============================================================================
// 测试用例
// ============================================================================

// 1. GPA 计算 — 空列表
void test_gpa_empty()
{
    TEST("GPA 空课程列表")
    double gpa = GpaLogic::calculateGPA({});
    ASSERT_EQ(gpa, 0.0, "空列表应返回 0.0");
}

// 2. GPA 计算 — 单门课程
void test_gpa_single()
{
    TEST("GPA 单门课程")
    QList<Course> courses = {
        Course("高等数学", 4.0, 85.0)
    };
    double gpa = GpaLogic::calculateGPA(courses);
    ASSERT_EQ(gpa, 85.0, "单门课程 GPA = 成绩本身");
}

// 3. GPA 计算 — 多门加权
void test_gpa_weighted()
{
    TEST("GPA 多门加权")
    QList<Course> courses = {
        Course("高数", 4.0, 80.0),   // 4*80 = 320
        Course("英语", 2.0, 90.0),   // 2*90 = 180
        Course("体育", 1.0, 70.0),   // 1*70 = 70
    };
    // total = 320+180+70 = 570, credits = 7, gpa = 570/7 ≈ 81.4286
    double gpa = GpaLogic::calculateGPA(courses);
    double expected = 570.0 / 7.0;
    ASSERT_EQ(qFuzzyCompare(gpa, expected), true, "加权 GPA 570/7 ≈ 81.43");
}

// 4. GPA 计算 — 学分为 0（安全除零）
void test_gpa_zero_credit()
{
    TEST("GPA 零学分")
    QList<Course> courses = {
        Course("讲座", 0.0, 95.0)
    };
    double gpa = GpaLogic::calculateGPA(courses);
    ASSERT_EQ(gpa, 0.0, "零学分应返回 0.0（除零保护）");
}

// 5. GPA 计算 — 负数学分/成绩（异常输入）
void test_gpa_negative()
{
    TEST("GPA 负分（异常输入）")
    QList<Course> courses = {
        Course("异常课", 3.0, -10.0)
    };
    double gpa = GpaLogic::calculateGPA(courses);
    ASSERT_EQ(gpa, -10.0, "负成绩：原样输出加权结果（不做修正）");
}

// 6. JSON 课程存取
void test_json_courses()
{
    TEST("JSON 课程存取")
    QString path = "test_courses.json";

    QList<Course> input = {
        Course("C++", 3.0, 92.0),
        Course("数据结构", 4.0, 88.5)
    };

    bool saved = DataManager::saveCourses(path, input);
    ASSERT_TRUE(saved, "保存课程到 JSON");

    QList<Course> loaded = DataManager::loadCourses(path);
    ASSERT_EQ(loaded.size(), 2, "加载课程数量 = 2");
    ASSERT_EQ(loaded[0].name, QString("C++"), "第一门名称 = C++");
    ASSERT_EQ(loaded[0].credit, 3.0, "第一门学分 = 3.0");
    ASSERT_EQ(loaded[0].grade, 92.0, "第一门成绩 = 92.0");

    QFile::remove(path); // 清理
}

// 7. JSON 经历存取（全类型覆盖）
void test_json_experiences()
{
    TEST("JSON 经历存取（四类型）")
    QString path = "test_experiences.json";

    QList<Experience> input = {
        Experience(ExperienceType::Internship, "会计实习生", "XX公司",
                   QDate(2024, 2, 1), QDate(2024, 3, 31), "凭证整理"),
        Experience(ExperienceType::Project, "创新创业大赛", "校团委",
                   QDate(2023, 5, 1), QDate(2023, 6, 30), "商业计划书"),
        Experience(ExperienceType::Activity, "社团秘书处", "学生会",
                   QDate(2021, 10, 1), QDate(2024, 4, 30), "沟通协调"),
        Experience(ExperienceType::Other, "志愿者", "社区",
                   QDate(2022, 1, 1), QDate(), "无结束日期"),
    };

    bool saved = DataManager::saveExperiences(path, input);
    ASSERT_TRUE(saved, "保存经历到 JSON");

    QList<Experience> loaded = DataManager::loadExperiences(path);
    ASSERT_EQ(loaded.size(), 4, "加载经历数量 = 4");
    ASSERT_EQ(static_cast<int>(loaded[0].type), static_cast<int>(ExperienceType::Internship), "类型还原正确");

    // 验证 dates
    ASSERT_EQ(loaded[3].endDate.isValid(), false, "空日期正确还原（至今）");

    QFile::remove(path);
}

// 8. JSON 完整数据包存取
void test_json_package()
{
    TEST("JSON 完整数据包存取")
    QString path = "test_package.json";

    ResumePackage pkg;
    pkg.fullName  = "测试用户";
    pkg.contact   = "13800000000";
    pkg.targetJob = "测试工程师";
    pkg.skills    = "C++/Qt";
    pkg.finalGpa  = 3.55;
    pkg.courses.append(Course("测试课", 2.0, 90.0));
    pkg.experiences.append(Experience(
        ExperienceType::Internship,
        "测试实习生", "测试公司",
        QDate(2025, 1, 1), QDate(2025, 6, 1), "测试"));

    bool saved = DataManager::savePackage(path, pkg);
    ASSERT_TRUE(saved, "保存完整数据包");

    ResumePackage loaded = DataManager::loadPackage(path);
    ASSERT_EQ(loaded.fullName, QString("测试用户"), "姓名");
    ASSERT_EQ(loaded.finalGpa, 3.55, "GPA");
    ASSERT_EQ(loaded.courses.size(), 1, "课程数量 = 1");
    ASSERT_EQ(loaded.experiences.size(), 1, "经历数量 = 1");

    QFile::remove(path);
}

// 9. JSON 读取不存在文件
void test_json_missing_file()
{
    TEST("JSON 读取不存在文件")
    QList<Course> loaded = DataManager::loadCourses("__nonexistent__.json");
    ASSERT_EQ(loaded.size(), 0, "文件不存在 → 返回空列表");
}

// 10. 日期格式化
void test_date_range()
{
    TEST("日期区间格式化")
    Experience e1(ExperienceType::Internship, "t", "o",
                  QDate(2024, 2, 1), QDate(2024, 3, 31), "d");
    ASSERT_EQ(e1.dateRange(), QString("2024.02 - 2024.03"), "完整区间");

    Experience e2(ExperienceType::Internship, "t", "o",
                  QDate(2021, 9, 1), QDate(), "d");
    ASSERT_EQ(e2.dateRange(), QString("2021.09 - 至今"), "至今");

    Experience e3(ExperienceType::Internship, "t", "o",
                  QDate(), QDate(), "d");
    ASSERT_EQ(e3.dateRange(), QString(""), "无效日期 → 空字符串");
}

// 11. PDF 导出
void test_pdf_export()
{
    TEST("PDF 导出 (基于 resume_sample.json)")
    QString samplePath = "resume_sample.json";
    if (!QFile::exists(samplePath)) {
        // 尝试从 exe 目录寻找
        samplePath = QCoreApplication::applicationDirPath() + "/resume_sample.json";
    }
    if (!QFile::exists(samplePath)) {
        samplePath = "../resume_sample.json";
    }
    if (!QFile::exists(samplePath)) {
        samplePath = "../../resume_sample.json";
    }

    if (!QFile::exists(samplePath)) {
        qDebug() << "  [FAIL] 未能找到 resume_sample.json，无法进行 PDF 导出测试";
        g_failed++;
        return;
    }

    ResumePackage pkg = DataManager::loadPackage(samplePath);
    
    ASSERT_EQ(pkg.fullName.isEmpty(), false, "样板姓名非空校验");
    ASSERT_TRUE(pkg.courses.size() >= 10, "样板包含至少 10 门课程");
    ASSERT_TRUE(pkg.experiences.size() >= 2, "样板包含至少 2 段经历");

    // 重新核算 GPA 确保正常
    pkg.finalGpa = GpaLogic::calculateGPA(pkg.courses);

    QString path = "resume_sample_output.pdf";
    bool ok = ResumeExporter::exportToPdf(pkg, path);

    if (ok) {
        ASSERT_TRUE(QFile::exists(path), "样板 PDF 文件已生成");
        qint64 size = QFileInfo(path).size();
        qDebug() << "  [INFO] PDF size:" << size << "bytes";
        ASSERT_TRUE(size > 0, "样板 PDF 文件大小 > 0");
        qDebug() << "  [INFO] 已成功输出测试样板 PDF 至:" << QFileInfo(path).absoluteFilePath();
    } else {
        qDebug() << "  [SKIP] PDF 导出需要 QPrinter（GUI 环境），CI 中可能跳过";
    }
}

// 12. HTML 生成（不依赖 QPrinter，纯逻辑验证）
void test_html_build()
{
    TEST("HTML 构建")
    ResumePackage pkg;
    pkg.fullName  = "HTML测试";
    pkg.contact   = "html@test.com";
    pkg.courses.append(Course("语文", 2.0, 80.0));

    QString html = ResumeExporter::buildHtml(pkg);
    ASSERT_TRUE(html.contains("HTML测试"), "HTML 包含姓名");
    ASSERT_TRUE(html.contains("语文"), "HTML 包含课程名");
    ASSERT_TRUE(html.contains("<!DOCTYPE html>"), "HTML 具有 DOCTYPE");
    ASSERT_TRUE(html.contains("<style>"), "HTML 包含内嵌 CSS");
}

// 13. 大量数据压力测试
void test_stress()
{
    TEST("压力测试：1000 门课程 + 100 条经历")
    QList<Course> largeCourses;
    for (int i = 0; i < 1000; ++i) {
        largeCourses.append(Course(QString("课程%1").arg(i), 2.0, 85.0));
    }
    double gpa = GpaLogic::calculateGPA(largeCourses);
    ASSERT_EQ(gpa, 85.0, "1000 门课 GPA = 85.0");

    ResumePackage pkg;
    pkg.fullName = "Stress";
    pkg.courses = largeCourses;
    for (int i = 0; i < 100; ++i) {
        pkg.experiences.append(Experience(
            ExperienceType::Project,
            QString("项目%1").arg(i), "机构",
            QDate(2020, 1, 1), QDate(2020, 2, 1), ""));
    }

    QString html = ResumeExporter::buildHtml(pkg);
    ASSERT_TRUE(html.length() > 10000, "大 HTML 长度 > 10000");
    qDebug() << "  [INFO] HTML length:" << html.length() << "chars";
}


// ============================================================================
// 入口
// ============================================================================

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qDebug() << "╔══════════════════════════════════╗";
    qDebug() << "║   BDT220 自动化单元测试          ║";
    qDebug() << "╚══════════════════════════════════╝";

    // ---- 执行测试 ----
    test_gpa_empty();
    test_gpa_single();
    test_gpa_weighted();
    test_gpa_zero_credit();
    test_gpa_negative();

    test_json_courses();
    test_json_experiences();
    test_json_package();
    test_json_missing_file();

    test_date_range();
    test_html_build();
    test_pdf_export();      // 可能因无 GUI 跳过
    test_stress();

    // ---- 汇总 ----
    qDebug() << "\n╔══════════════════════════════════╗";
    qDebug() << "║  测试结果: PASS =" << g_passed << "FAIL =" << g_failed;
    qDebug() << "╚══════════════════════════════════╝";

    return g_failed > 0 ? 1 : 0;
}
