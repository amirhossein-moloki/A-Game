from PyQt6.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QLabel, QLineEdit, QComboBox, QPushButton, QHBoxLayout, QMessageBox
from PyQt6.QtCore import Qt
from app.logic.profile_manager import ProfileManager

class MappingWindow(QMainWindow):
    def __init__(self, main_window, profile_name=None):
        super().__init__()
        self.main_window = main_window
        self.profile_manager = ProfileManager()
        self.setWindowTitle("ساخت/ویرایش پروفایل")
        self.setGeometry(150, 150, 900, 700)

        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        main_layout = QVBoxLayout(central_widget)

        self.profile_name_input = QLineEdit()
        if profile_name:
            self.profile_name_input.setText(profile_name)
        else:
            self.profile_name_input.setPlaceholderText("نام پروفایل را وارد کنید...")
        main_layout.addWidget(self.profile_name_input)

        self.device_selector = QComboBox()
        self.device_selector.addItems(["Xbox Controller", "PlayStation Controller", "Keyboard & Mouse"])
        main_layout.addWidget(self.device_selector)

        self.controller_image_label = QLabel("تصویر کنترلر در اینجا نمایش داده می‌شود")
        self.controller_image_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.controller_image_label.setMinimumSize(600, 400)
        main_layout.addWidget(self.controller_image_label)

        button_layout = QHBoxLayout()
        self.save_button = QPushButton("ذخیره")
        self.save_button.clicked.connect(self.save_profile)
        self.cancel_button = QPushButton("لغو")
        self.cancel_button.clicked.connect(self.close_window)
        button_layout.addWidget(self.save_button)
        button_layout.addWidget(self.cancel_button)
        main_layout.addLayout(button_layout)

        self.apply_styles()

    def save_profile(self):
        profile_name = self.profile_name_input.text().strip()
        if not profile_name:
            QMessageBox.warning(self, "خطا", "نام پروفایل نمی‌تواند خالی باشد.")
            return

        data = {
            "device": self.device_selector.currentText(),
            "mappings": {} # Placeholder for actual mappings
        }

        try:
            self.profile_manager.save_profile(profile_name, data)
            self.close_window()
        except Exception as e:
            QMessageBox.critical(self, "خطا در ذخیره‌سازی", f"مشکلی در ذخیره پروفایل رخ داد:\n{e}")

    def close_window(self):
        self.main_window.load_profiles()
        self.main_window.show()
        self.close()

    def apply_styles(self):
        self.setStyleSheet("""
            QMainWindow { background-color: #282c34; color: #ffffff; }
            QLineEdit, QComboBox { background-color: #3c4049; color: #ffffff; border: 1px solid #61afef; padding: 5px; border-radius: 5px; }
            QLabel { color: #ffffff; }
            QPushButton { background-color: #61afef; color: #ffffff; border: none; padding: 10px; border-radius: 5px; }
            QPushButton:hover { background-color: #5298d8; }
        """)
