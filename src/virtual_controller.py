import vgamepad as vg
import winreg
import webbrowser

def is_vigem_installed():
    try:
        # Check for the ViGEmBus driver in the Windows registry
        key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, r"SYSTEM\CurrentControlSet\Services\ViGEmBus")
        winreg.CloseKey(key)
        return True
    except FileNotFoundError:
        return False

class VirtualController:
    def __init__(self):
        if not is_vigem_installed():
            print("ViGEmBus driver not found. Please install it from https://github.com/ViGEm/ViGEmBus/releases")
            webbrowser.open("https://github.com/ViGEm/ViGEmBus/releases")
            raise SystemExit("ViGEmBus driver not found.")
        self.gamepad = vg.VX360Gamepad()

    def press_button(self, button):
        self.gamepad.press_button(button=button)
        self.gamepad.update()

    def release_button(self, button):
        self.gamepad.release_button(button=button)
        self.gamepad.update()

    def left_joystick_float(self, x_value_float, y_value_float):
        self.gamepad.left_joystick_float(x_value_float=x_value_float, y_value_float=y_value_float)
        self.gamepad.update()

    def right_joystick_float(self, x_value_float, y_value_float):
        self.gamepad.right_joystick_float(x_value_float=x_value_float, y_value_float=y_value_float)
        self.gamepad.update()

    def left_trigger_float(self, value_float):
        self.gamepad.left_trigger_float(value_float=value_float)
        self.gamepad.update()

    def right_trigger_float(self, value_float):
        self.gamepad.right_trigger_float(value_float=value_float)
        self.gamepad.update()
