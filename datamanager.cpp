#include "datamanager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDate>

// ============================================================================
// 工具：类型 <-> 字符串
// ============================================================================

QString DataManager::typeToString(ExperienceType t)
{
    switch (t) {
    case ExperienceType::Internship: return QStringLiteral("internship");
    case ExperienceType::Project:    return QStringLiteral("project");
    case ExperienceType::Activity:   return QStringLiteral("activity");
    default:                         return QStringLiteral("other");
    }
}

ExperienceType DataManager::stringToType(const QString& s)
{
    if (s == QStringLiteral("internship")) return ExperienceType::Internship;
    if (s == QStringLiteral("project"))    return ExperienceType::Project;
    if (s == QStringLiteral("activity"))   return ExperienceType::Activity;
    return ExperienceType::Other;
}


// ============================================================================
// 课程存取
// ============================================================================

bool DataManager::saveCourses(const QString& filePath,
                              const QList<Course>& courses)
{
    QJsonArray arr;
    for (const auto& c : courses) {
        QJsonObject obj;
        obj[QStringLiteral("name")]   = c.name;
        obj[QStringLiteral("credit")] = c.credit;
        obj[QStringLiteral("grade")]  = c.grade;
        arr.append(obj);
    }

    QJsonDocument doc(arr);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

QList<Course> DataManager::loadCourses(const QString& filePath)
{
    QList<Course> result;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return result;

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError || !doc.isArray())
        return result;

    for (const auto& val : doc.array()) {
        QJsonObject obj = val.toObject();
        Course c;
        c.name   = obj[QStringLiteral("name")].toString();
        c.credit = obj[QStringLiteral("credit")].toDouble();
        c.grade  = obj[QStringLiteral("grade")].toDouble();
        result.append(c);
    }
    return result;
}


// ============================================================================
// 经历存取
// ============================================================================

bool DataManager::saveExperiences(const QString& filePath,
                                  const QList<Experience>& experiences)
{
    QJsonArray arr;
    for (const auto& e : experiences) {
        QJsonObject obj;
        obj[QStringLiteral("type")]         = typeToString(e.type);
        obj[QStringLiteral("title")]        = e.title;
        obj[QStringLiteral("organization")] = e.organization;
        obj[QStringLiteral("startDate")]    = e.startDate.toString(Qt::ISODate);
        obj[QStringLiteral("endDate")]      = e.endDate.toString(Qt::ISODate);
        obj[QStringLiteral("description")]  = e.description;
        arr.append(obj);
    }

    QJsonDocument doc(arr);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

QList<Experience> DataManager::loadExperiences(const QString& filePath)
{
    QList<Experience> result;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return result;

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError || !doc.isArray())
        return result;

    for (const auto& val : doc.array()) {
        QJsonObject obj = val.toObject();
        Experience e;
        e.type         = stringToType(obj[QStringLiteral("type")].toString());
        e.title        = obj[QStringLiteral("title")].toString();
        e.organization = obj[QStringLiteral("organization")].toString();
        e.startDate    = QDate::fromString(obj[QStringLiteral("startDate")].toString(), Qt::ISODate);
        e.endDate      = QDate::fromString(obj[QStringLiteral("endDate")].toString(), Qt::ISODate);
        e.description  = obj[QStringLiteral("description")].toString();
        result.append(e);
    }
    return result;
}


// ============================================================================
// 完整数据包存取
// ============================================================================

bool DataManager::savePackage(const QString& filePath,
                              const ResumePackage& pkg)
{
    QJsonObject root;
    root[QStringLiteral("fullName")]  = pkg.fullName;
    root[QStringLiteral("contact")]   = pkg.contact;
    root[QStringLiteral("targetJob")] = pkg.targetJob;
    root[QStringLiteral("skills")]    = pkg.skills;
    root[QStringLiteral("finalGpa")]  = pkg.finalGpa;

    QJsonArray coursesArr;
    for (const auto& c : pkg.courses) {
        QJsonObject co;
        co[QStringLiteral("name")]   = c.name;
        co[QStringLiteral("credit")] = c.credit;
        co[QStringLiteral("grade")]  = c.grade;
        coursesArr.append(co);
    }
    root[QStringLiteral("courses")] = coursesArr;

    QJsonArray expArr;
    for (const auto& e : pkg.experiences) {
        QJsonObject eo;
        eo[QStringLiteral("type")]         = typeToString(e.type);
        eo[QStringLiteral("title")]        = e.title;
        eo[QStringLiteral("organization")] = e.organization;
        eo[QStringLiteral("startDate")]    = e.startDate.toString(Qt::ISODate);
        eo[QStringLiteral("endDate")]      = e.endDate.toString(Qt::ISODate);
        eo[QStringLiteral("description")]  = e.description;
        expArr.append(eo);
    }
    root[QStringLiteral("experiences")] = expArr;

    QJsonDocument doc(root);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

ResumePackage DataManager::loadPackage(const QString& filePath)
{
    ResumePackage pkg;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return pkg;

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject())
        return pkg;

    QJsonObject root = doc.object();
    pkg.fullName  = root[QStringLiteral("fullName")].toString();
    pkg.contact   = root[QStringLiteral("contact")].toString();
    pkg.targetJob = root[QStringLiteral("targetJob")].toString();
    pkg.skills    = root[QStringLiteral("skills")].toString();
    pkg.finalGpa  = root[QStringLiteral("finalGpa")].toDouble();

    QJsonArray coursesArr = root[QStringLiteral("courses")].toArray();
    for (const auto& val : coursesArr) {
        QJsonObject co = val.toObject();
        Course c;
        c.name   = co[QStringLiteral("name")].toString();
        c.credit = co[QStringLiteral("credit")].toDouble();
        c.grade  = co[QStringLiteral("grade")].toDouble();
        pkg.courses.append(c);
    }

    QJsonArray expArr = root[QStringLiteral("experiences")].toArray();
    for (const auto& val : expArr) {
        QJsonObject eo = val.toObject();
        Experience e;
        e.type         = stringToType(eo[QStringLiteral("type")].toString());
        e.title        = eo[QStringLiteral("title")].toString();
        e.organization = eo[QStringLiteral("organization")].toString();
        e.startDate    = QDate::fromString(eo[QStringLiteral("startDate")].toString(), Qt::ISODate);
        e.endDate      = QDate::fromString(eo[QStringLiteral("endDate")].toString(), Qt::ISODate);
        e.description  = eo[QStringLiteral("description")].toString();
        pkg.experiences.append(e);
    }

    return pkg;
}
