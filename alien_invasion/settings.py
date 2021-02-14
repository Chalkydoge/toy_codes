
class Settings:
	'''存储设置的类'''

	def __init__(self):
		# 屏幕设置
		self.screen_width = 1200
		self.screen_height = 800
		self.bg_color = (230, 230, 230)
		self.score_scale = 1.5

		# 子弹设置
		self.bullet_width = 300
		self.bullet_height = 15
		self.bullet_color = (60, 60, 60)
		self.bullets_allowed = 3

		# 外星人设置
		self.fleet_drop_speed = 10

		# 飞船设置
		self.ship_limit = 3

		# 动态设置
		self.speedup_scale_dict = {"Easy" : 1.05, "Medium" : 1.2, "Hard": 1.5}
		self.score_scale_dict = {"Easy" : 1.5, "Medium" : 2.0, "Hard": 3.0}
		self.alien_points_dict = {"Easy" : 50, "Medium" : 75, "Hard": 125}
		self.alien_speed_dict = {"Easy" : 1.0, "Medium" : 1.2, "Hard": 1.5}
		self.initialize_dynamic_settings()


	def initialize_dynamic_settings(self, mode="Easy"):
		self.ship_speed = 1.5
		self.bullet_speed = 3.0
		self.alien_speed = self.alien_speed_dict[mode]
		# 1代表右移 -1代表左移
		self.fleet_direction = 1
		self.alien_points = self.alien_points_dict[mode]
		self.score_scale = self.score_scale_dict[mode]
		self.speedup_scale = self.speedup_scale_dict[mode]

	def increase_speed(self):
		self.ship_speed *= self.speedup_scale
		self.bullet_speed *= self.speedup_scale
		self.alien_speed *= self.speedup_scale
		self.alien_points = int(self.alien_points * self.score_scale)