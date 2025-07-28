from PyQt6.QtWidgets import QMainWindow, QLabel, QWidget, QVBoxLayout, QListWidget, QPushButton
from PyQt6.QtCore import Qt
from app.mapping_window import MappingWindow
from app.logic.profile_manager import ProfileManager

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Rewasd Mapper")
        self.setGeometry(100, 100, 800, 600)
        self.profile_manager = ProfileManager()
        self.mapping_window = None # To hold the reference to the mapping window

        # Main widget and layout
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        layout = QVBoxLayout(central_widget)

        # Active Profile Display
        self.active_profile_label = QLabel("پروفایل فعال: None")
        self.active_profile_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        font = self.active_profile_label.font()
        font.setPointSize(16)
        self.active_profile_label.setFont(font)
        layout.addWidget(self.active_profile_label)

        # Profiles List
        self.profile_list_widget = QListWidget()
        layout.addWidget(self.profile_list_widget)

        # Add New Profile Button
        self.add_profile_button = QPushButton("+")
        self.add_profile_button.clicked.connect(self.open_mapping_window)
        font = self.add_profile_button.font()
        font.setPointSize(20)
        self.add_profile_button.setFont(font)
        self.add_profile_button.setFixedSize(50, 50)
        layout.addWidget(self.add_profile_button, alignment=Qt.AlignmentFlag.AlignRight)

        self.load_profiles()
        self.apply_styles()

    def load_profiles(self):
        """Clears and loads profile names into the list widget."""
        self.profile_list_widget.clear()
        profiles = self.profile_manager.get_profiles()
        self.profile_list_widget.addItems(profiles)

    def open_mapping_window(self):
        """Opens the mapping window to create a new profile."""
        # Pass self to mapping_window to call back load_profiles
        self.mapping_window = MappingWindow(main_window=self)
        self.mapping_window.show()
        self.hide() # Hide main window

    def apply_styles(self):
        self.setStyleSheet("""
            QMainWindow { background-color: #282c34; }
            QLabel { color: #ffffff; }
            QListWidget { background-color: #3c4049; color: #ffffff; border: none; font-size: 14px; }
            QListWidget::item { padding: 10px; }
            QListWidget::item:hover { background-color: #4a4e57; }
            QListWidget::item:selected { background-color: #61afef; }
            QPushButton { background-color: #61afef; color: #ffffff; border-radius: 25px; border: none; }
            QPushButton:hover { background-color: #5298d8; }
        """)
