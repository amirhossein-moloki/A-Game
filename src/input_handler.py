import evdev
import threading

class InputHandler:
    def __init__(self, mapping_engine):
        self.mapping_engine = mapping_engine
        self.devices = [evdev.InputDevice(path) for path in evdev.list_devices()]
        self.threads = []

    def start(self):
        for device in self.devices:
            thread = threading.Thread(target=self.listen, args=(device,), daemon=True)
            thread.start()
            self.threads.append(thread)

    def listen(self, device):
        for event in device.read_loop():
            if event.type == evdev.ecodes.EV_KEY:
                key_event = evdev.categorize(event)
                event_type = "press" if key_event.keystate == key_event.key_down else "release"
                self.mapping_engine.process_event(event_type, key_event.keycode)

    def stop(self):
        # The threads are daemonized, so they will exit when the main thread exits.
        # A more graceful shutdown might be needed in a real application.
        pass
