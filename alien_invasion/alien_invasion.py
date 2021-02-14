import sys
import pygame
from time import sleep
from settings import Settings
from ship import Ship
from bullet import Bullet
from alien import Alien
from game_stats import GameStats
from button import Button
from scoreboard import Scoreboard
from difficulty import Difficulty

class AlienInvasion:
	'''docstring'''

	def __init__(self):
		'''init the game screen'''
		pygame.init()
		# 游戏设置
		self.settings = Settings()
		# 屏幕
		self.screen = pygame.display.set_mode((self.settings.screen_width, self.settings.screen_height))
		self.ship = Ship(self)
		self.bullets = pygame.sprite.Group()
		self.aliens = pygame.sprite.Group()
		# 难度选项按钮
		self.difficulty = Difficulty(self)
		self.gaming = False
		self._create_fleet()
		# 标题设置
		pygame.display.set_caption("Alien Invasion")
		self.stats = GameStats(self)
		self.play_button = Button(self, "Play")
		self.sb = Scoreboard(self)
		self.fire_sound = pygame.mixer.Sound("music/Explosion_Cannon_Fire_02.wav")
		self.ship_hit_sound = pygame.mixer.Sound("music/Explosion_With_Debris_01.wav")
		self.game_over_sound = pygame.mixer.Sound("music/Gameover.wav")

	def run_game(self):
		'''start game'''
		while True:
			# 辅助方法, 注意命名以_开头
			self._check_events()
			if self.stats.game_active and self.stats.mode_selection_active:
				self.ship.update()
				self._update_bullet()
				self._update_aliens()
			self._update_screen()

	def _check_events(self):
		# 监视键盘和鼠标事件
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				self._store_highscore()
				sys.exit()
			elif event.type == pygame.KEYDOWN:
				self._check_keydown_events(event)
			elif event.type == pygame.KEYUP:
				self._check_keyup_events(event)
			elif event.type == pygame.MOUSEBUTTONDOWN:
				mouse_pos = pygame.mouse.get_pos()
				if not self.stats.game_active:
					self._check_play_button(mouse_pos)
				elif not self.stats.mode_selection_active:
					self._check_mode_button(mouse_pos)
   
	def _check_keydown_events(self, event):
		if event.key == pygame.K_RIGHT:
			# 向右移动, 增大center_x
			self.ship.moving_right = True
		elif event.key == pygame.K_LEFT:
			# 向左移动, 更新标记
			self.ship.moving_left = True
		elif event.key == pygame.K_q:
			self._store_highscore()
			sys.exit()
		elif event.key == pygame.K_SPACE:
			self._fire_bullet()
		elif event.key == pygame.K_p and not self.stats.game_active:
			self._start_game()
			self.settings.initialize_dynamic_settings()

	def _check_keyup_events(self, event):
		'''响应松开按键'''
		if event.key == pygame.K_RIGHT:
			# 松开右键, 取消标记
			self.ship.moving_right = False
		elif event.key == pygame.K_LEFT:
			self.ship.moving_left = False

	def _check_play_button(self, mouse_pos):
		'''在玩家单击play时开始新游戏'''
		if self.gaming or self.stats.mode_selection_active:
			return
		button_clicked = self.play_button.rect.collidepoint(mouse_pos)
		if button_clicked and not self.stats.game_active:
			self.stats.game_active = True
		self.stats.mode_selection_active = False
		return

	def _check_mode_button(self, mouse_pos):
		if self.gaming or not self.stats.game_active:
			return

		mode_selected = ""
		mode_clicked = False
		for mode, mode_rect in self.difficulty.mode_rects.items():
			mode_clicked = mode_rect.collidepoint(mouse_pos)
			# print(mode, mode_clicked)
			if mode_clicked and self.stats.game_active and not self.stats.mode_selection_active:
				mode_selected = mode
				self.stats.mode_selection_active = True
				break

		if self.stats.game_active and self.stats.mode_selection_active:
			self._start_game()
			self.settings.initialize_dynamic_settings(mode_selected)
			self.sb.prep_score()
			self.sb.prep_level()
			self.sb.prep_ships()

	def _start_game(self):
		self.stats.reset_stats()
		self.stats.game_active = True
		self.stats.mode_selection_active = True
		self.gaming = True
		self.aliens.empty()
		self.bullets.empty()

		self._create_fleet()
		self.ship.center_ship()
		pygame.mouse.set_visible(False)

	def _update_screen(self):
		# 每一次循环都重新绘制
		self.screen.fill(self.settings.bg_color)
		self.ship.blitme()

		# 画出子弹图形
		for bullet in self.bullets.sprites():
			bullet.draw_bullet()

		self.aliens.draw(self.screen)
		self.sb.show_score()
		
		if not self.stats.game_active and not self.stats.mode_selection_active:
			self.play_button.draw_button()   
		elif self.stats.game_active and not self.stats.mode_selection_active:
			self.difficulty.draw_modes()

		# 让最近绘制的屏幕可见 
		pygame.display.flip()

	def _update_bullet(self):
		self.bullets.update()
		# 删除子弹
		for bullet in self.bullets.copy(): #注意循环一个列表时必须保证其长度不变，所以需要对它的副本进行遍历
			if bullet.rect.bottom <= 0:
				self.bullets.remove(bullet)
		self._check_bullet_alien_collisions()

	def _check_bullet_alien_collisions(self):
		collisions = pygame.sprite.groupcollide(self.bullets, self.aliens, True, True)
		if collisions:
			for aliens in collisions.values():
				self.stats.score += self.settings.alien_points * len(aliens)
			self.sb.prep_score()
			self.sb.check_high_score()

		if not self.aliens:
			self.bullets.empty()
			self._create_fleet()
			self.settings.increase_speed()

			self.stats.level += 1
			self.sb.prep_level()

	def _fire_bullet(self):
		if len(self.bullets) < self.settings.bullets_allowed:
			new_bullet = Bullet(self)
			self.bullets.add(new_bullet)
		self.fire_sound.play(loops=0, maxtime=500)

	def _create_fleet(self):
		'''创建外星人群'''
		alien = Alien(self)
		alien_width, alien_height = alien.rect.size
		ship_height = self.ship.rect.height
		available_space_x = self.settings.screen_width - (2 * alien_width)
		available_space_y = self.settings.screen_height -  \
							(3 * alien_width) - ship_height
		number_rows = available_space_y // (2 * alien_height)
		number_aliens_x = available_space_x // (2 * alien_width)

		for row_number in range(number_rows):
			for alien_number in range(number_aliens_x):
				self._create_alien(alien_number, row_number)

	def _create_alien(self, alien_number, row_number):
		'''创建一个外星人并放在当前行'''
		alien = Alien(self)
		alien_width, alien_height = alien.rect.size
		alien.x = alien_width + 2 * alien_width * alien_number
		alien.rect.x = alien.x
		alien.y = alien_height + 2 * alien_height * row_number
		alien.rect.y = alien.y
		self.aliens.add(alien)

	def _check_fleet_edges(self):
		''''''
		for alien in self.aliens.sprites():
			if alien.check_edges():
				self._change_fleet_direction()
				break

	def _change_fleet_direction(self):
		''''''
		for alien in self.aliens.sprites():
			alien.rect.y += self.settings.fleet_drop_speed
		self.settings.fleet_direction *= -1 

	def _update_aliens(self):
		'''更新外星人群中所有外星人的位置'''
		self._check_fleet_edges()
		self.aliens.update()

		if pygame.sprite.spritecollideany(self.ship, self.aliens):
			self._ship_hit()
		self._check_aliens_bottom()

	def _ship_hit(self):
		if self.stats.ships_left > 0:
			self.stats.ships_left -= 1
			self.sb.prep_ships()
			self.aliens.empty()
			self.bullets.empty()
			self._create_fleet()
			self.ship.center_ship()
			self.ship_hit_sound.play(loops=0, maxtime=1000)
			sleep(0.5)
		else:
			self.stats.game_active = False
			self.stats.mode_selection_active = False
			self.gaming = False
			self.game_over_sound.play()
			pygame.mouse.set_visible(True)
		# print(self.stats.game_active, self.stats.mode_selection_active)

	def _check_aliens_bottom(self):
		screen_rect = self.screen.get_rect()
		for alien in self.aliens.sprites():
			if alien.rect.bottom >= screen_rect.bottom:
				self._ship_hit()
				break

	def _store_highscore(self):
		with open("score.txt", 'w') as f:
			f.write(str(self.stats.high_score))

if __name__ == '__main__':
	# 创建游戏实例并运行游戏
	ai = AlienInvasion()
	ai.run_game()
