import pygame
from pygame.sprite import Sprite

class Ship(Sprite):
	''' 管理飞船的类 '''

	def __init__(self, ai_game):
		super().__init__()
		
		self.screen = ai_game.screen
		self.settings = ai_game.settings
		self.screen_rect = ai_game.screen.get_rect()

		# 加载飞船图片并获得外接矩阵
		self.image = pygame.image.load('images/ship.bmp')
		self.rect = self.image.get_rect()

		# 对每一艘新飞船，将其放置在屏幕底部的中央
		self.rect.midbottom = self.screen_rect.midbottom

		# 在飞船的属性x中存储浮点值
		self.x = float(self.rect.x)

		# 移动标志
		self.moving_right = False
		self.moving_left = False

	def blitme(self):
		'''在指定位置绘制飞船'''
		self.screen.blit(self.image, self.rect)

	def update(self):
		# 根据飞船的移动标志不断调整位置
		# 更新飞船的x 而不是rect对象
		if self.moving_right and self.rect.right < self.screen_rect.right:
			self.x += self.settings.ship_speed
		if self.moving_left and self.rect.left > 0:
			self.x -= self.settings.ship_speed

		# 使用浮点值的x更新rect对象
		self.rect.x = self.x

	def center_ship(self):
		self.rect.midbottom = self.screen_rect.midbottom
		self.x = float(self.rect.x)