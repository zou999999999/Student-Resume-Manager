# 文件处理与导出
实现 DataManager JSON 序列化持久化类，安全读写本地文件，保证重启不丢数据。
实现 ExperienceType 枚举与字符串的双向转化，处理 loadPackage() 加载缺失文件及 JSON 损毁的容错机制。
实现 ResumeExporter 简历打印引擎，包含 buildHtml() HTML 样式生成、QTextDocument 排版绑定及 QPrinter 虚拟 PDF 打印控制。
编写 .toHtmlEscaped() 方法转义所有危险输入占位符，防御 HTML/Script 脚本注入，保护导出安全性。

## 核心文件清单
- `datamanager.h/cpp` — JSON 文件编解码与持久化
- `model_layers.h/cpp` (中的 `ResumeExporter` 导出引擎)
