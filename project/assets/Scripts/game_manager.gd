extends Node

static var current_area = 1
static var area_path = "res://assets/scenes/areas/"

static func set_next_level():
	current_area += 1
	return area_path + "areas_" + str(current_area) + ".tscn"
	
func go_next_level(path):
	get_tree().change_scene_to_file(path)
	print("The player has moved to area")
