# 📂 文件处理与导出

## 👤 成员信息
- **姓名**: 组员 周宇恒
- **项目角色**: 文件处理与导出

## 🛠️ 主要负责与完成内容
- 实现 DataManager JSON 序列化持久化类，安全读写本地文件，保证重启不丢数据。
- 实现 ExperienceType 枚举与字符串的双向转化，处理 loadPackage() 加载缺失文件及 JSON 损毁的容错机制。
- 实现 ResumeExporter 简历打印引擎，包含 buildHtml() HTML 样式生成、QTextDocument 排版绑定及 QPrinter 虚拟 PDF 打印控制。
- 编写 .toHtmlEscaped() 方法转义所有危险输入占位符，防御 HTML/Script 脚本注入，保护导出安全性。

## 📄 本模块核心文件清单
- `datamanager.h/cpp` — JSON 文件编解码与持久化
- `model_layers.h/cpp` (中的 `ResumeExporter` 导出引擎)

## 🚀 编译与运行方式
本文件夹包含完整的 Qt 项目结构，确保该模块可以被独立编译及测试。
1. 使用 Qt Creator 打开本目录下的 `BDT220new.pro` 项目文件。
2. 配置好编译器（如 Desktop Qt 6.x.x MinGW 64-bit）。
3. 点击「构建项目」并运行。
