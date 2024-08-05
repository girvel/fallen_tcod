local tcod = require("fallen_tcod")

print("-- running tests --")
assert(tcod.add(2, 2) == 4, "2 + 2 should be equal 4")
assert(tcod.get_x(tcod.create_vector(2, 0)) == 2, "userdata should work")
assert(tcod.create_map(2, 2), "create_map should create some object")
print("Success!")
