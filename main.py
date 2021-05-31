import pygame
import random
import os
import neat

pygame.init()
h=0

font = pygame.font.Font('freesansbold.ttf', 30)
font1 = pygame.font.Font('freesansbold.ttf', 30)
font2 = pygame.font.Font('freesansbold.ttf', 30)

p=pygame.image.load("pipes(1).png")
screen = pygame.display.set_mode((700,600))
pygame.display.set_caption("Space invaders")

class Birds:
    def __init__(self, x5, y5):
        self.im = pygame.image.load('ufo.png')
        self.xm = x5
        self.ym = y5

    def move(self):
        self.ym += 20

    def draw(self):
        screen.blit(self.im, (self.xm, self.ym))


    def jump(self):
        self.ym -= 25


    def get_mask(self):


       return pygame.mask.from_surface(self.im)


class Pipe:



    def __init__(self, x):

        self.x = x
        self.height = 0


        self.top = 0
        self.bottom = 0

        self.PIPE_TOP =p
        self.PIPE_BOTTOM = p

        self.passed = False

        self.set_height()

    def set_height(self):

        self.height = random.randrange(236,300)
        self.top = random.randint(-120,-10)
        self.bottom =random.randint(350,450)

    def move(self):

        self.x -= 10

    def draw(self,screen):


        screen.blit(self.PIPE_TOP, (self.x, self.top))

        screen.blit(self.PIPE_BOTTOM, (self.x, self.bottom))


    def collide(self, bird, screen):

        bird_mask = bird.get_mask()
        top_mask = pygame.mask.from_surface(self.PIPE_TOP)
        bottom_mask = pygame.mask.from_surface(self.PIPE_BOTTOM)
        top_offset = (self.x - bird.xm, self.top - round(bird.ym))
        bottom_offset = (self.x - bird.xm, self.bottom - round(bird.ym))

        b_point = bird_mask.overlap(bottom_mask, bottom_offset)
        t_point = bird_mask.overlap(top_mask,top_offset)

        if b_point or t_point:
            return True

        return False

class background:

    def __init__(self, bb, bb1):
        self.bb = bb
        self.bb1 = bb1
        self.m1 = pygame.image.load('1624.png')

    def move(self):
        self.bb -= 5
        if self.bb < -4000:
            self.bb = 0
            self.bb1 = 0

    def draw(self):

        screen.blit(self.m1, (self.bb, self.bb1))
        screen.blit(self.m1, (self.bb + 3000, self.bb1))


def draw_window(screen, birds, pipes, back, c, h):
    back.draw()
    for pipe in pipes:
        pipe.draw(screen)
    for bird in birds:

        bird.draw()
    c1 = font.render("Score :" + str(c), True, (255, 255, 255))
    screen.blit(c1, (10, 10))
    c2 = font1.render("Gen :" + str(h), True, (255, 255, 255))
    screen.blit(c2, (550, 10))


    pygame.display.update()


def main(genomes, config):

    global  h
    h+= 1
    nets = []
    birds = []
    ge = []
    for _, g in genomes:
        net = neat.nn.FeedForwardNetwork.create(g, config)
        nets.append(net)
        birds.append(Birds(30, 100))

        g.fitness = 0
        ge.append(g)

    back = background(0, -700)
    pipes = [Pipe(450)]
    score = 0
    run = True
    while run and len(birds) > 0:


        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
                pygame.quit()
                quit()
                break

        pipe_ind = 0
        if len(birds) > 0:
            if len(pipes) > 1 and birds[0].xm > pipes[0].x + pipes[0].PIPE_TOP.get_width():
                pipe_ind = 1

        for x, bird in enumerate(birds):
            ge[x].fitness += 0.1
            bird.move()


            output = nets[x].activate((bird.ym, abs(bird.ym - pipes[pipe_ind].height), abs(bird.ym - pipes[pipe_ind].bottom)))

            if output[0] > 0.5:
                bird.jump()

        back.move()

        rem = []
        add_pipe = False
        for pipe in pipes:
            pipe.move()

            for x,bird in enumerate(birds):
                if pipe.collide(bird, screen):
                    ge[x].fitness -= 1
                    nets.pop((x))
                    ge.pop(x)
                    birds.pop(x)

            if pipe.x + pipe.PIPE_TOP.get_width() < 0:
                rem.append(pipe)

            if not pipe.passed and pipe.x < bird.xm:
                pipe.passed = True
                add_pipe = True

        if add_pipe:
            score += 1

            for g in ge:
                g.fitness += 5
            pipes.append(Pipe(600))

        for r in rem:
            pipes.remove(r)

        for c,bird in enumerate(birds):
            if bird.ym>550 or bird.ym<10:
                nets.pop(c)
                ge.pop(c)
                birds.pop(c)

        draw_window(screen, birds, pipes, back, score, h)
def run(config_file):

    config = neat.config.Config(neat.DefaultGenome, neat.DefaultReproduction,
                         neat.DefaultSpeciesSet, neat.DefaultStagnation,
                         config_file)  
    p = neat.Population(config)
    p.add_reporter(neat.StdOutReporter(True))
    stats = neat.StatisticsReporter()
    p.add_reporter(stats)
    winner = p.run(main, 50)
if __name__ == '__main__':

    local_dir = os.path.dirname(__file__)
    config_path = os.path.join(local_dir, 'Untitled Document 1.txt.')
    run(config_path)


