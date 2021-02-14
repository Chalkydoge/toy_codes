
class GameStats:
	
	def __init__(self, ai_game):
		'''游戏状态设置类'''
		
		# 游戏是否处于play阶段
		self.game_active = False
		# 增加一个难度选择阶段
		self.mode_selection_active = False
		self.settings = ai_game.settings
		self.reset_stats()
		
		with open("score.txt", 'r') as f:
			lines = f.readlines()
			high_score_str = ''
			for line in lines:
				high_score_str += line.strip()
			self.high_score = int(high_score_str)
		
		self.level = 0
		
	def reset_stats(self):
		self.ships_left = self.settings.ship_limit
		self.score = 0
		self.level = 0