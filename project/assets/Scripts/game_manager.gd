extends Node

static var current_area = 1
static var area_path = "res://assets/scenes/areas/"

static func set_next_level():
	current_area += 1
	return area_path + "area_" + str(current_area) + ".tscn"
