from pynput import keyboard, mouse

class InputHandler:
    def __init__(self, mapping_engine):
        self.mapping_engine = mapping_engine
        self.keyboard_listener = keyboard.Listener(on_press=self.on_press, on_release=self.on_release)
        self.mouse_listener = mouse.Listener(on_click=self.on_click)

    def on_press(self, key):
        try:
            self.mapping_engine.process_event("press", key.char)
        except AttributeError:
            self.mapping_engine.process_event("press", key.name)

    def on_release(self, key):
        try:
            self.mapping_engine.process_event("release", key.char)
        except AttributeError:
            self.mapping_engine.process_event("release", key.name)

    def on_click(self, x, y, button, pressed):
        event_type = "press" if pressed else "release"
        # To match the JSON format, we'll use "left" and "right" for mouse buttons
        button_name = f"Mouse_{button.name}"
        self.mapping_engine.process_event(event_type, button_name)

    def start(self):
        self.keyboard_listener.start()
        self.mouse_listener.start()

    def stop(self):
        self.keyboard_listener.stop()
        self.mouse_listener.stop()
