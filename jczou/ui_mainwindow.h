/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *rootLayout;
    QTabWidget *tabWidget;
    QWidget *tabAcademic;
    QVBoxLayout *academicLayout;
    QGroupBox *grpCourseInput;
    QHBoxLayout *courseInputLayout;
    QLabel *lblName;
    QLineEdit *edit_course_name;
    QLabel *lblCredit;
    QLineEdit *edit_course_credit;
    QLabel *lblScore;
    QLineEdit *edit_course_score;
    QPushButton *btn_calc_gpa;
    QTableWidget *twCourses;
    QHBoxLayout *courseBtnRow;
    QPushButton *btnRemoveCourse;
    QSpacerItem *hSpacerCourse;
    QLabel *label_gpa_result;
    QWidget *tabExperience;
    QVBoxLayout *expLayout;
    QGroupBox *grpExpInput;
    QVBoxLayout *expInputLayout;
    QHBoxLayout *expRow1;
    QLabel *lblExpType;
    QComboBox *cbExpType;
    QLabel *lblExpTitle;
    QLineEdit *leExpTitle;
    QLabel *lblExpOrg;
    QLineEdit *leExpOrg;
    QHBoxLayout *expRow2;
    QLabel *lblStart;
    QLineEdit *edit_start_date;
    QLabel *lblEnd;
    QLineEdit *edit_end_date;
    QSpacerItem *hSpacerExp;
    QPushButton *btnAddExp;
    QHBoxLayout *expRow3;
    QLabel *lblExpDesc;
    QTextEdit *teExpDesc;
    QTableWidget *twExperiences;
    QPushButton *btnRemoveExp;
    QWidget *tabExport;
    QVBoxLayout *exportLayout;
    QGroupBox *grpPersonal;
    QVBoxLayout *personalLayout;
    QHBoxLayout *rowName;
    QLabel *lblName2;
    QLineEdit *edit_full_name;
    QHBoxLayout *rowContact;
    QLabel *lblContact2;
    QLineEdit *edit_contact;
    QHBoxLayout *rowTarget;
    QLabel *lblTarget;
    QLineEdit *edit_target_job;
    QGroupBox *grpSkills;
    QVBoxLayout *skillsLayout;
    QTextEdit *edit_skills;
    QLabel *lblSummary;
    QPushButton *btn_load_sample;
    QPushButton *btn_export_pdf;
    QLabel *label_status_msg;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(694, 540);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        rootLayout = new QVBoxLayout(centralWidget);
        rootLayout->setObjectName("rootLayout");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabAcademic = new QWidget();
        tabAcademic->setObjectName("tabAcademic");
        academicLayout = new QVBoxLayout(tabAcademic);
        academicLayout->setObjectName("academicLayout");
        grpCourseInput = new QGroupBox(tabAcademic);
        grpCourseInput->setObjectName("grpCourseInput");
        courseInputLayout = new QHBoxLayout(grpCourseInput);
        courseInputLayout->setObjectName("courseInputLayout");
        lblName = new QLabel(grpCourseInput);
        lblName->setObjectName("lblName");

        courseInputLayout->addWidget(lblName);

        edit_course_name = new QLineEdit(grpCourseInput);
        edit_course_name->setObjectName("edit_course_name");

        courseInputLayout->addWidget(edit_course_name);

        lblCredit = new QLabel(grpCourseInput);
        lblCredit->setObjectName("lblCredit");

        courseInputLayout->addWidget(lblCredit);

        edit_course_credit = new QLineEdit(grpCourseInput);
        edit_course_credit->setObjectName("edit_course_credit");

        courseInputLayout->addWidget(edit_course_credit);

        lblScore = new QLabel(grpCourseInput);
        lblScore->setObjectName("lblScore");

        courseInputLayout->addWidget(lblScore);

        edit_course_score = new QLineEdit(grpCourseInput);
        edit_course_score->setObjectName("edit_course_score");

        courseInputLayout->addWidget(edit_course_score);

        btn_calc_gpa = new QPushButton(grpCourseInput);
        btn_calc_gpa->setObjectName("btn_calc_gpa");

        courseInputLayout->addWidget(btn_calc_gpa);


        academicLayout->addWidget(grpCourseInput);

        twCourses = new QTableWidget(tabAcademic);
        if (twCourses->columnCount() < 3)
            twCourses->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twCourses->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        twCourses->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        twCourses->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        twCourses->setObjectName("twCourses");
        twCourses->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        twCourses->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        twCourses->horizontalHeader()->setStretchLastSection(true);

        academicLayout->addWidget(twCourses);

        courseBtnRow = new QHBoxLayout();
        courseBtnRow->setObjectName("courseBtnRow");
        btnRemoveCourse = new QPushButton(tabAcademic);
        btnRemoveCourse->setObjectName("btnRemoveCourse");

        courseBtnRow->addWidget(btnRemoveCourse);

        hSpacerCourse = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        courseBtnRow->addItem(hSpacerCourse);


        academicLayout->addLayout(courseBtnRow);

        label_gpa_result = new QLabel(tabAcademic);
        label_gpa_result->setObjectName("label_gpa_result");

        academicLayout->addWidget(label_gpa_result);

        tabWidget->addTab(tabAcademic, QString());
        tabExperience = new QWidget();
        tabExperience->setObjectName("tabExperience");
        expLayout = new QVBoxLayout(tabExperience);
        expLayout->setObjectName("expLayout");
        grpExpInput = new QGroupBox(tabExperience);
        grpExpInput->setObjectName("grpExpInput");
        expInputLayout = new QVBoxLayout(grpExpInput);
        expInputLayout->setObjectName("expInputLayout");
        expRow1 = new QHBoxLayout();
        expRow1->setObjectName("expRow1");
        lblExpType = new QLabel(grpExpInput);
        lblExpType->setObjectName("lblExpType");

        expRow1->addWidget(lblExpType);

        cbExpType = new QComboBox(grpExpInput);
        cbExpType->addItem(QString());
        cbExpType->addItem(QString());
        cbExpType->addItem(QString());
        cbExpType->addItem(QString());
        cbExpType->setObjectName("cbExpType");

        expRow1->addWidget(cbExpType);

        lblExpTitle = new QLabel(grpExpInput);
        lblExpTitle->setObjectName("lblExpTitle");

        expRow1->addWidget(lblExpTitle);

        leExpTitle = new QLineEdit(grpExpInput);
        leExpTitle->setObjectName("leExpTitle");

        expRow1->addWidget(leExpTitle);

        lblExpOrg = new QLabel(grpExpInput);
        lblExpOrg->setObjectName("lblExpOrg");

        expRow1->addWidget(lblExpOrg);

        leExpOrg = new QLineEdit(grpExpInput);
        leExpOrg->setObjectName("leExpOrg");

        expRow1->addWidget(leExpOrg);


        expInputLayout->addLayout(expRow1);

        expRow2 = new QHBoxLayout();
        expRow2->setObjectName("expRow2");
        lblStart = new QLabel(grpExpInput);
        lblStart->setObjectName("lblStart");

        expRow2->addWidget(lblStart);

        edit_start_date = new QLineEdit(grpExpInput);
        edit_start_date->setObjectName("edit_start_date");

        expRow2->addWidget(edit_start_date);

        lblEnd = new QLabel(grpExpInput);
        lblEnd->setObjectName("lblEnd");

        expRow2->addWidget(lblEnd);

        edit_end_date = new QLineEdit(grpExpInput);
        edit_end_date->setObjectName("edit_end_date");

        expRow2->addWidget(edit_end_date);

        hSpacerExp = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        expRow2->addItem(hSpacerExp);

        btnAddExp = new QPushButton(grpExpInput);
        btnAddExp->setObjectName("btnAddExp");

        expRow2->addWidget(btnAddExp);


        expInputLayout->addLayout(expRow2);

        expRow3 = new QHBoxLayout();
        expRow3->setObjectName("expRow3");
        lblExpDesc = new QLabel(grpExpInput);
        lblExpDesc->setObjectName("lblExpDesc");

        expRow3->addWidget(lblExpDesc);

        teExpDesc = new QTextEdit(grpExpInput);
        teExpDesc->setObjectName("teExpDesc");

        expRow3->addWidget(teExpDesc);


        expInputLayout->addLayout(expRow3);


        expLayout->addWidget(grpExpInput);

        twExperiences = new QTableWidget(tabExperience);
        if (twExperiences->columnCount() < 4)
            twExperiences->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        twExperiences->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        twExperiences->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        twExperiences->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        twExperiences->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        twExperiences->setObjectName("twExperiences");
        twExperiences->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        twExperiences->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        twExperiences->horizontalHeader()->setStretchLastSection(true);

        expLayout->addWidget(twExperiences);

        btnRemoveExp = new QPushButton(tabExperience);
        btnRemoveExp->setObjectName("btnRemoveExp");

        expLayout->addWidget(btnRemoveExp);

        tabWidget->addTab(tabExperience, QString());
        tabExport = new QWidget();
        tabExport->setObjectName("tabExport");
        exportLayout = new QVBoxLayout(tabExport);
        exportLayout->setObjectName("exportLayout");
        grpPersonal = new QGroupBox(tabExport);
        grpPersonal->setObjectName("grpPersonal");
        personalLayout = new QVBoxLayout(grpPersonal);
        personalLayout->setObjectName("personalLayout");
        rowName = new QHBoxLayout();
        rowName->setObjectName("rowName");
        lblName2 = new QLabel(grpPersonal);
        lblName2->setObjectName("lblName2");
        lblName2->setMinimumSize(QSize(70, 0));

        rowName->addWidget(lblName2);

        edit_full_name = new QLineEdit(grpPersonal);
        edit_full_name->setObjectName("edit_full_name");

        rowName->addWidget(edit_full_name);


        personalLayout->addLayout(rowName);

        rowContact = new QHBoxLayout();
        rowContact->setObjectName("rowContact");
        lblContact2 = new QLabel(grpPersonal);
        lblContact2->setObjectName("lblContact2");
        lblContact2->setMinimumSize(QSize(70, 0));

        rowContact->addWidget(lblContact2);

        edit_contact = new QLineEdit(grpPersonal);
        edit_contact->setObjectName("edit_contact");

        rowContact->addWidget(edit_contact);


        personalLayout->addLayout(rowContact);

        rowTarget = new QHBoxLayout();
        rowTarget->setObjectName("rowTarget");
        lblTarget = new QLabel(grpPersonal);
        lblTarget->setObjectName("lblTarget");
        lblTarget->setMinimumSize(QSize(70, 0));

        rowTarget->addWidget(lblTarget);

        edit_target_job = new QLineEdit(grpPersonal);
        edit_target_job->setObjectName("edit_target_job");

        rowTarget->addWidget(edit_target_job);


        personalLayout->addLayout(rowTarget);


        exportLayout->addWidget(grpPersonal);

        grpSkills = new QGroupBox(tabExport);
        grpSkills->setObjectName("grpSkills");
        skillsLayout = new QVBoxLayout(grpSkills);
        skillsLayout->setObjectName("skillsLayout");
        edit_skills = new QTextEdit(grpSkills);
        edit_skills->setObjectName("edit_skills");

        skillsLayout->addWidget(edit_skills);


        exportLayout->addWidget(grpSkills);

        lblSummary = new QLabel(tabExport);
        lblSummary->setObjectName("lblSummary");

        exportLayout->addWidget(lblSummary);

        btn_load_sample = new QPushButton(tabExport);
        btn_load_sample->setObjectName("btn_load_sample");
        btn_load_sample->setMinimumHeight(30);

        exportLayout->addWidget(btn_load_sample);

        btn_export_pdf = new QPushButton(tabExport);
        btn_export_pdf->setObjectName("btn_export_pdf");
        btn_export_pdf->setMinimumHeight(40);

        exportLayout->addWidget(btn_export_pdf);

        label_status_msg = new QLabel(tabExport);
        label_status_msg->setObjectName("label_status_msg");

        exportLayout->addWidget(label_status_msg);

        tabWidget->addTab(tabExport, QString());

        rootLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\344\270\252\344\272\272\345\255\246\344\270\232\344\270\216\347\256\200\345\216\206\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        grpCourseInput->setTitle(QCoreApplication::translate("MainWindow", "\345\275\225\345\205\245\350\257\276\347\250\213", nullptr));
        lblName->setText(QCoreApplication::translate("MainWindow", "\350\257\276\347\250\213\345\220\215\347\247\260", nullptr));
        edit_course_name->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\246\202\357\274\232\351\253\230\347\255\211\346\225\260\345\255\246", nullptr));
        lblCredit->setText(QCoreApplication::translate("MainWindow", "\345\255\246\345\210\206", nullptr));
        edit_course_credit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\246\202\357\274\2324.0", nullptr));
        lblScore->setText(QCoreApplication::translate("MainWindow", "\346\210\220\347\273\251(0-100)", nullptr));
        edit_course_score->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\246\202\357\274\23285", nullptr));
        btn_calc_gpa->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { font-weight: bold; color: #c0392b; }", nullptr));
        btn_calc_gpa->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\345\271\266\350\256\241\347\256\227 GPA", nullptr));
        QTableWidgetItem *___qtablewidgetitem = twCourses->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\350\257\276\347\250\213\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = twCourses->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\345\255\246\345\210\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = twCourses->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\346\210\220\347\273\251", nullptr));
        btnRemoveCourse->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\351\200\211\344\270\255\350\257\276\347\250\213", nullptr));
        label_gpa_result->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 18px; font-weight: bold; color: #2a6496; padding: 8px;", nullptr));
        label_gpa_result->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215 GPA\357\274\232--", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabAcademic), QCoreApplication::translate("MainWindow", "\345\255\246\344\270\232\347\256\241\347\220\206", nullptr));
        grpExpInput->setTitle(QCoreApplication::translate("MainWindow", "\345\275\225\345\205\245\347\273\217\345\216\206", nullptr));
        lblExpType->setText(QCoreApplication::translate("MainWindow", "\347\261\273\345\236\213", nullptr));
        cbExpType->setItemText(0, QCoreApplication::translate("MainWindow", "\345\256\236\344\271\240\347\273\217\345\216\206", nullptr));
        cbExpType->setItemText(1, QCoreApplication::translate("MainWindow", "\351\241\271\347\233\256\347\273\217\345\216\206", nullptr));
        cbExpType->setItemText(2, QCoreApplication::translate("MainWindow", "\346\240\241\345\233\255\347\273\217\345\216\206", nullptr));
        cbExpType->setItemText(3, QCoreApplication::translate("MainWindow", "\345\205\266\344\273\226", nullptr));

        lblExpTitle->setText(QCoreApplication::translate("MainWindow", "\346\240\207\351\242\230", nullptr));
        leExpTitle->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\246\202\357\274\232\344\274\232\350\256\241\345\256\236\344\271\240\347\224\237", nullptr));
        lblExpOrg->setText(QCoreApplication::translate("MainWindow", "\346\234\272\346\236\204", nullptr));
        leExpOrg->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\246\202\357\274\232XX\345\205\254\345\217\270", nullptr));
        lblStart->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213(YYYY.MM)", nullptr));
        edit_start_date->setPlaceholderText(QCoreApplication::translate("MainWindow", "2024.02", nullptr));
        lblEnd->setText(QCoreApplication::translate("MainWindow", "\347\273\223\346\235\237(YYYY.MM)", nullptr));
        edit_end_date->setPlaceholderText(QCoreApplication::translate("MainWindow", "2024.03", nullptr));
        btnAddExp->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\347\273\217\345\216\206", nullptr));
        lblExpDesc->setText(QCoreApplication::translate("MainWindow", "\346\217\217\350\277\260", nullptr));
        teExpDesc->setPlaceholderText(QCoreApplication::translate("MainWindow", "\347\256\200\350\246\201\346\217\217\350\277\260\350\277\231\346\256\265\347\273\217\345\216\206...", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = twExperiences->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = twExperiences->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\346\240\207\351\242\230", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = twExperiences->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\346\234\272\346\236\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = twExperiences->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "\346\227\266\351\227\264", nullptr));
        btnRemoveExp->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\351\200\211\344\270\255\347\273\217\345\216\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabExperience), QCoreApplication::translate("MainWindow", "\345\261\245\345\216\206\347\264\240\346\235\220\345\272\223", nullptr));
        grpPersonal->setTitle(QCoreApplication::translate("MainWindow", "\344\270\252\344\272\272\344\277\241\346\201\257", nullptr));
        lblName2->setText(QCoreApplication::translate("MainWindow", "\345\247\223\345\220\215", nullptr));
        edit_full_name->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\247\223\345\220\215\357\274\210\345\277\205\345\241\253\357\274\211", nullptr));
        lblContact2->setText(QCoreApplication::translate("MainWindow", "\350\201\224\347\263\273\346\226\271\345\274\217", nullptr));
        edit_contact->setPlaceholderText(QCoreApplication::translate("MainWindow", "\347\224\265\350\257\235 / \351\202\256\347\256\261", nullptr));
        lblTarget->setText(QCoreApplication::translate("MainWindow", "\346\261\202\350\201\214\346\204\217\345\220\221", nullptr));
        edit_target_job->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\246\202\357\274\232\350\275\257\344\273\266\345\274\200\345\217\221\345\267\245\347\250\213\345\270\210", nullptr));
        grpSkills->setTitle(QCoreApplication::translate("MainWindow", "\346\212\200\350\203\275 / \350\257\201\344\271\246", nullptr));
        edit_skills->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\246\202\357\274\232CET-6\343\200\201\350\256\241\347\256\227\346\234\272\344\272\214\347\272\247\343\200\201\347\206\237\347\273\203\346\216\214\346\217\241 C++/Qt...", nullptr));
        lblSummary->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 14px; color: #555; padding: 8px;", nullptr));
        lblSummary->setText(QCoreApplication::translate("MainWindow", "\345\267\262\345\275\225\345\205\245 0 \351\227\250\350\257\276\347\250\213 | 0 \346\256\265\347\273\217\345\216\206 | GPA\357\274\232--", nullptr));
        btn_load_sample->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { font-size: 13px; color: #333; background-color: #f8f9fa; border: 1px solid #ced4da; border-radius: 4px; } QPushButton:hover { background-color: #e2e6ea; }", nullptr));
        btn_load_sample->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\346\265\213\350\257\225\346\240\267\346\235\277\346\225\260\346\215\256 (10\351\227\250\350\257\276\347\250\213+3\346\256\265\347\273\217\345\216\206)", nullptr));
        btn_export_pdf->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { font-size: 16px; font-weight: bold; background-color: #2a6496; color: white; border-radius: 4px; } QPushButton:hover { background-color: #1d4f7a; }", nullptr));
        btn_export_pdf->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\345\257\274\345\207\272 Word \347\256\200\345\216\206", nullptr));
        label_status_msg->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 13px; color: #666; padding: 4px;", nullptr));
        label_status_msg->setText(QCoreApplication::translate("MainWindow", "\345\260\261\347\273\252", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabExport), QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\347\256\200\345\216\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
