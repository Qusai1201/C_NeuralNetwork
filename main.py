import pyautogui
from PIL import ImageGrab

def get_pixel_color(x, y):
    screen = ImageGrab.grab()
    pixel_color = screen.getpixel((x, y))
    return pixel_color

# Get the current mouse cursor position
mouse_x, mouse_y = pyautogui.position()

# Get the color of the pixel at the mouse cursor position
pixel_color = get_pixel_color(mouse_x, mouse_y)

print(f"Mouse Position: ({mouse_x}, {mouse_y})")
print(f"Pixel Color: {pixel_color}")