#!/usr/bin/env python3
import sys
import subprocess
from PySide6 import QtWidgets, QtCore

class BootloaderGUI(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("MTKClient Bootloader Tool")
        self.resize(600, 400)

        # عناصر الواجهة
        self.unlock_btn = QtWidgets.QPushButton("Unlock Bootloader")
        self.lock_btn   = QtWidgets.QPushButton("Lock Bootloader")
        self.log_output = QtWidgets.QPlainTextEdit()
        self.log_output.setReadOnly(True)

        # تخطيط العناصر
        btn_layout = QtWidgets.QHBoxLayout()
        btn_layout.addWidget(self.unlock_btn)
        btn_layout.addWidget(self.lock_btn)

        main_layout = QtWidgets.QVBoxLayout(self)
        main_layout.addLayout(btn_layout)
        main_layout.addWidget(self.log_output)

        # ربط الأزرار بوظائفها
        self.unlock_btn.clicked.connect(lambda: self.run_cmd("unlock"))
        self.lock_btn.clicked.connect(lambda: self.run_cmd("lock"))

    def run_cmd(self, mode):
        """يشغل mtkclient da seccfg unlock أو lock ويعرض اللوق"""
        # افتح وضع BROM (الجهاز مفصول/مطفي مع preloader)
        cmd = [sys.executable, "mtk.py", "da", "seccfg", mode]
        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)

        self.log_output.appendPlainText(f"> تشغيل: {' '.join(cmd)}\n")
        for line in proc.stdout:
            self.log_output.appendPlainText(line.rstrip())
            QtCore.QCoreApplication.processEvents()  # لتحديث الواجهة أثناء خروج اللوج
        proc.wait()
        self.log_output.appendPlainText(f"\n-- انتهى ({mode}) --\n")

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    win = BootloaderGUI()
    win.show()
    sys.exit(app.exec())
