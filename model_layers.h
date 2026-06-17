#ifndef MODEL_LAYERS_H
#define MODEL_LAYERS_H

#include <QString>
#include <QList>
#include <QDate>

// ============================================================================
// 核心数据结构
// ============================================================================

/// 课程信息
struct Course
{
    QString name;       //课程名称
    double credit;     //学分
    double grade;      //成绩（百分制或四分制均可，GPA 计算时调用方统一为同一制度）

    Course() : credit(0.0), grade(0.0) {}
    Course(const QString& n, double c, double g)
        : name(n), credit(c), grade(g) {}
};

/// 经历类型枚举
enum class ExperienceType
{
    Internship,   // 实习经历
    Project,      // 项目经历
    Activity,     // 校园/社会活动
    Other
};

/// 经历
inline QString experienceTypeName(ExperienceType t)
{
    switch (t) {
    case ExperienceType::Internship: return QStringLiteral("实习经历");
    case ExperienceType::Project:    return QStringLiteral("项目经历");
    case ExperienceType::Activity:   return QStringLiteral("校园经历");
    default:                         return QStringLiteral("其他");
    }
}

/// 一段经历（实习/项目/活动）
struct Experience
{
    ExperienceType  type;         //经历类型
    QString         title;        // 经历标题（如岗位名称、项目名称）
    QString         organization; // 机构/组织
    QDate           startDate;    // 开始时间
    QDate           endDate;      // 结束时间
    QString         description;  // 描述（支持换行符 \n）

    Experience()
        : type(ExperienceType::Other) {}

    Experience(ExperienceType tp,
               const QString& t,
               const QString& org,
               const QDate&   s,
               const QDate&   e,
               const QString& desc)
        : type(tp), title(t), organization(org)
        , startDate(s), endDate(e), description(desc) {}

    /// 格式化日期区间，如 "2021.09 - 2025.06" 或 "至今"
    QString dateRange() const;
};

/// 简历数据包 —— 汇总一份完整简历所需的所有数据
struct ResumePackage
{
    QString           fullName;       ///< 姓名
    QString           contact;        ///< 联系方式（电话 / 邮箱 / 微信）
    QList<Course>     courses;        ///< 课程列表
    QList<Experience> experiences;    ///< 各类经历
    double            finalGpa;       ///< 综合 GPA
    QString           targetJob;      ///< 求职意向（可选）
    QString           skills;         ///< 技能/证书（自由文本，支持 HTML 片段）

    ResumePackage() : finalGpa(0.0) {}
};


// ============================================================================
// 算法类：GPA 计算
// ============================================================================

class GpaLogic
{
public:
    GpaLogic() = default;

    /// 计算加权平均绩点
    /// 若总学分为 0，返回 0.0
    static double calculateGPA(const QList<Course>& courseList);

    /// 同时返回总学分和加权总分，方便上层做进一步统计
    static void calculateDetail(const QList<Course>& courseList,
                                double& totalCredits,
                                double& weightedSum);
};


// ============================================================================
// 导出类：简历 → PDF
// ============================================================================

class ResumeExporter
{
public:
    ResumeExporter() = default;

    /// 将简历数据包导出为 PDF 文件
    /// @param package  简历数据
    /// @param savePath 目标文件完整路径（含 .pdf 后缀）
    /// @return true 导出成功
    static bool exportToPdf(const ResumePackage& package,
                            const QString& savePath);

    /// 将简历数据包导出为 Word 文件 (实际为 HTML 格式)
    /// @param package  简历数据
    /// @param savePath 目标文件完整路径（含 .doc 后缀）
    /// @return true 导出成功
    static bool exportToWord(const ResumePackage& package,
                             const QString& savePath);

    /// 根据 ResumePackage 生成完整的 HTML 简历字符串（内嵌 CSS 排版）
    static QString buildHtml(const ResumePackage& pkg);
};

#endif // MODEL_LAYERS_H
