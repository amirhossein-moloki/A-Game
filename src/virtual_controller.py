import vgamepad as vg

class VirtualController:
    def __init__(self):
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
