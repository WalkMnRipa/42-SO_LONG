import random
import os

MAX_WIDTH = 60
MAX_HEIGHT = 34
TILE_SIZE = 32
MIN_ROOM_SIZE = 5
MAX_ROOM_SIZE = 10
MAX_ROOMS = 20

class Room:
    def __init__(self, x, y, w, h):
        self.x1 = x
        self.y1 = y
        self.x2 = x + w
        self.y2 = y + h

    def center(self):
        center_x = (self.x1 + self.x2) // 2
        center_y = (self.y1 + self.y2) // 2
        return (center_x, center_y)

    def intersects(self, other):
        return (self.x1 <= other.x2 and self.x2 >= other.x1 and
                self.y1 <= other.y2 and self.y2 >= other.y1)

def create_room(map_data, room):
    for x in range(room.x1 + 1, room.x2):
        for y in range(room.y1 + 1, room.y2):
            map_data[y][x] = '0'

def create_h_tunnel(map_data, x1, x2, y):
    for x in range(min(x1, x2), max(x1, x2) + 1):
        map_data[y][x] = '0'

def create_v_tunnel(map_data, y1, y2, x):
    for y in range(min(y1, y2), max(y1, y2) + 1):
        map_data[y][x] = '0'

def generate_map(width, height):
    map_data = [['1' for _ in range(width)] for _ in range(height)]
    rooms = []
    min_rooms = random.randint(3, 8)
    num_rooms = random.randint(min_rooms, MAX_ROOMS)

    for _ in range(num_rooms):
        w = random.randint(MIN_ROOM_SIZE, MAX_ROOM_SIZE)
        h = random.randint(MIN_ROOM_SIZE, MAX_ROOM_SIZE)
        x = random.randint(1, width - w - 1)
        y = random.randint(1, height - h - 1)

        new_room = Room(x, y, w, h)

        if not any(new_room.intersects(other_room) for other_room in rooms):
            create_room(map_data, new_room)

            if rooms:
                (new_x, new_y) = new_room.center()
                for _ in range(random.randint(1, 2)):  # Create 1 to 2 paths
                    prev_room = random.choice(rooms)
                    (prev_x, prev_y) = prev_room.center()

                    if random.random() < 0.5:
                        create_h_tunnel(map_data, prev_x, new_x, prev_y)
                        create_v_tunnel(map_data, prev_y, new_y, new_x)
                    else:
                        create_v_tunnel(map_data, prev_y, new_y, prev_x)
                        create_h_tunnel(map_data, prev_x, new_x, new_y)

            rooms.append(new_room)

    # Place player 'P'
    start_room = rooms[0]
    px, py = start_room.center()
    map_data[py][px] = 'P'

    # Place exit 'E'
    end_room = rooms[-1]
    ex, ey = end_room.center()
    map_data[ey][ex] = 'E'

    # Place collectibles 'C'
    total_floor_tiles = sum(row.count('0') for row in map_data)
    min_collectibles = max(1, num_rooms // 3)
    max_collectibles = min(num_rooms - 1, total_floor_tiles // 40)
    num_collectibles = random.randint(min_collectibles, max_collectibles)

    for _ in range(num_collectibles):
        room = random.choice(rooms[1:-1])  # Exclude start and end rooms
        attempts = 0
        while attempts < 50:  # Limit attempts to avoid infinite loop
            cx, cy = random.randint(room.x1 + 1, room.x2 - 1), random.randint(room.y1 + 1, room.y2 - 1)
            if map_data[cy][cx] == '0':
                map_data[cy][cx] = 'C'
                break
            attempts += 1

    return map_data

def save_map(map_data, filename):
    directory = "maps"
    if not os.path.exists(directory):
        os.makedirs(directory)
    
    filepath = os.path.join(directory, filename)
    with open(filepath, 'w') as f:
        for row in map_data:
            f.write(''.join(row) + '\n')

def main():
    print(f"Maximum map size: {MAX_WIDTH}x{MAX_HEIGHT}")
    while True:
        try:
            width = int(input("Enter the width of the map: "))
            height = int(input("Enter the height of the map: "))
            
            if width > MAX_WIDTH or height > MAX_HEIGHT:
                print(f"The map size exceeds the limits ({MAX_WIDTH}x{MAX_HEIGHT}). It will be adjusted.")
            
            width = min(max(20, width), MAX_WIDTH)
            height = min(max(20, height), MAX_HEIGHT)
            
            map_data = generate_map(width, height)
            
            filename = f"map_{len(map_data[0])}x{len(map_data)}.ber"
            save_map(map_data, filename)
            
            print(f"Map generated and saved in maps/{filename}")
            print(f"Final map dimensions: {len(map_data[0])}x{len(map_data)}")
            for row in map_data:
                print(''.join(row))
            
            break
        except ValueError:
            print("Please enter valid numbers for width and height.")

if __name__ == "__main__":
    main()