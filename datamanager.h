#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QList>

#include "model_layers.h"

/// 本地 JSON 持久化管理器
///
/// 将课程、经历、个人信息读写为本地 JSON 文件，
/// 保证软件重启后数据不丢失。
class DataManager
{
public:
    DataManager() = default;

    // ---------- 单项存取 ----------

    /// 保存课程列表到 JSON 文件
    static bool saveCourses(const QString& filePath,
                            const QList<Course>& courses);

    /// 从 JSON 文件加载课程列表
    static QList<Course> loadCourses(const QString& filePath);

    /// 保存经历列表到 JSON 文件
    static bool saveExperiences(const QString& filePath,
                                const QList<Experience>& experiences);

    /// 从 JSON 文件加载经历列表
    static QList<Experience> loadExperiences(const QString& filePath);

    // ---------- 完整数据包存取 ----------

    /// 将完整 ResumePackage 写入 JSON
    static bool savePackage(const QString& filePath,
                            const ResumePackage& pkg);

    /// 从 JSON 读取完整 ResumePackage
    static ResumePackage loadPackage(const QString& filePath);

private:
    /// 将 ExperienceType 枚举转为字符串
    static QString typeToString(ExperienceType t);
    /// 从字符串还原 ExperienceType
    static ExperienceType stringToType(const QString& s);
};

#endif // DATAMANAGER_H
