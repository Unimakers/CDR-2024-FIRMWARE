import tkinter as tk
import socket
import tk_tools
import math

class Compass(tk.Canvas):
    def __init__(self, master, size=200, *args, **kwargs):
        super().__init__(master, width=size, height=size, *args, **kwargs)
        self.size = size
        self.configure(bg="black")
        self.create_oval(5, 5, size - 5, size - 5, outline='white', width=2)  # Outer circle
        self.needle = self.create_line(size//2, size//2, size//2, 10, fill='red', width=3)  # Needle line
        self.angle = 0

    def set_angle(self, angle):
        self.angle = angle
        angle_rad = math.radians(angle)
        x = self.size // 2 + self.size // 2 * 0.8 * math.sin(angle_rad)
        y = self.size // 2 - self.size // 2 * 0.8 * math.cos(angle_rad)
        self.coords(self.needle, self.size // 2, self.size // 2, x, y)

def check_and_update_color():
    if is_true:
        root.configure(bg="red")
    else:
        root.configure(bg="blue")
    # Schedule the next check after 100 milliseconds
    root.after(100, check_and_update_color)

def udp_listener():
    global is_true
    UDP_IP = "0.0.0.0"
    UDP_PORT = 9999
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))
    
    while True:
        data, addr = sock.recvfrom(255)
        message = data.decode()
        try:
            if message.startswith("Y : "):
                angle = float(message.split(":")[1])
                compass.set_angle(angle)
            else:
                print("Invalid message format:", message)
        except ValueError:
            print("Invalid pitch value received:", message)

if __name__ == "__main__":

    is_true = False

    root = tk.Tk()
    root.geometry("1000x750")
    root.title("Background Color Toggle")

    # Call the function to start checking and updating the color
    check_and_update_color()

    # Start UDP listener in a separate thread
    import threading
    udp_thread = threading.Thread(target=udp_listener)
    udp_thread.start()

    # Label to display received message
    message_label = tk.Label(root, text="")
    message_label.pack(pady=10)

    compass = Compass(root, size=300)
    compass.pack(padx=20, pady=20)

    compass.set_angle(30)

    root.mainloop()