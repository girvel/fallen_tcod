local tcod = require("fallen_tcod")

print("-- running tests --")
assert(tcod.add(2, 2) == 4, "2 + 2 should be equal 4")
assert(tcod.get_x(tcod.create_vector(2, 0)) == 2, "userdata should work")

local map = tcod.map_create(2, 2)
tcod.map_set_properties(map, 1, 0, true, false)
assert(tcod.map_get_transparency(map, 1, 0) == true)
assert(tcod.map_get_transparency(map, 0, 0) == false)

tcod.map_compute_fov(map, 0, 0, 1, true, 0)
print("Success!")
