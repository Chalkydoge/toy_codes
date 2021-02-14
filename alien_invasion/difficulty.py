import pygame.font
from button import Button

class Difficulty:
	'''难度选项界面的设计
		__init__: 初始化设置

		_prep_msg: 将字符串信息渲染成图像

		draw_modes: 把它们画出来!
	'''
	def __init__(self, ai_game):

		self.screen = ai_game.screen
		self.screen_rect = self.screen.get_rect()
		self.width, self.height = 300, 50
		self.text_color = (255, 255, 255)
		self.center_x, self.center_y = self.screen_rect.center
		self.font = pygame.font.SysFont(None, 48)

		self.modes = ["Easy", "Medium", "Hard"]
		self.mode_color = { "Easy" : (0, 0, 255), "Medium" : (0, 255, 0), "Hard" : (255, 0, 0) }
		self.mode_pos = {"Easy" : (self.center_x, self.center_y - 175), \
						"Medium" : (self.center_x, self.center_y), "Hard" : (self.center_x, self.center_y + 175)}

		self.mode_rects = {"Easy" : pygame.Rect(0, 0, self.width, self.height), \
						"Medium" : pygame.Rect(0, 0, self.width, self.height), 		 \
						"Hard" : pygame.Rect(0, 0, self.width, self.height) }

	def _prep_msg(self, msg):
		self.msg_image = self.font.render(msg, True, self.text_color, self.mode_color[msg])
		self.msg_image_rect = self.msg_image.get_rect()
		self.msg_image_rect.center = self.mode_pos[msg]

	def draw_modes(self):
		for mode in self.modes:
			# 渲染文字
			self._prep_msg(mode)
			# 将对应颜色填充到按钮的矩形中
			self.mode_rects[mode].center = self.mode_pos[mode]
			self.screen.fill(self.mode_color[mode], self.mode_rects[mode])
			# 然后再把文字画上去
			self.screen.blit(self.msg_image, self.msg_image_rect)		
