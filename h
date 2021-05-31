def main(genomes,config):

    for _, g in genomes:
        net = neat.nn.FeedForwardNetwork.create(g,config)
        nets.append(net)
        bird.append(birds(30,100))

        g.fitness = 0
        ge.append(g)
def run(config_path):

    config = neat.config.Config(neat.DefaultGenome,neat.DefaultReproduction,neat.DefaultSpeciesSet,neat.DefaultStagnation,config_path)
    p = neat.Population(config)
    p.add_reporter(neat.StdOutReporter(True))
    stats=neat.StatisticsReporter()
    p.add_reporter(stats)
    winner = p.run(main,1)

if __name__ == "__main__" :

    local_dir = os.path.dirname(__file__)
    config_path = os.path.join(local_dir, "Untitled Document 1.txt ")
    run(config_path)
    bb -= 9
    if bb < -4000:
        bb = 0
        bb1 = 0
        import pygame
import random
import neat
import os

pygame.init()
h=0
screen = pygame.display.set_mode((800, 600))
font = pygame.font.Font('freesansbold.ttf', 30)
font1 = pygame.font.Font('freesansbold.ttf', 30)
font2 = pygame.font.Font('freesansbold.ttf', 30)


pygame.display.set_caption("SPACEINVADER")


class birds:
    def __init__(self, x5, y5):
        self.im = pygame.image.load('bee.png')
        self.xm = x5
        self.ym = y5

    def move(self):
        self.ym += 20

    def draw(self):
        screen.blit(self.im, (self.xm, self.ym))


    def jump(self):
        self.ym -= 25


class pipes(birds):

    def __init__(self, x1, x2, x3, xl1, xl2, xl3,x5,y5):
        super().__init__(x5, y5)
        self.x = x1
        self.x2 = x2
        self.xm = x5
        self.ym = y5
        self.x3 = x3
        self.xl1 = xl1
        self.xl2 = xl2
        self.xl3 = xl3
        self.y1 = random.randint(-100, -10)
        self.y2 = random.randint(-100, -10)
        self.y3 = random.randint(-100, -10)
        self.yl1 = random.randint(350, 400)
        self.yl2 = random.randint(350, 400)
        self.yl3 = random.randint(350, 400)
        self.b2 = pygame.image.load('pipes(1).png')
        self.b4 = pygame.image.load('pipes(1).png')
        self.b5 = pygame.image.load('pipes(1).png')
        self.bl1 = pygame.image.load('pipes(1).png')
        self.bl2 = pygame.image.load('pipes(1).png')
        self.bl3 = pygame.image.load('pipes(1).png')

    def move(self):
        self.x -= 5
        self.x2 -= 5
        self.x3 -= 5
        self.xl1 -= 5
        self.xl2 -= 5
        self.xl3 -= 5
        if self.x < -150:
            self.x = 750
        if self.x2 < -150:
            self.x2 = 750
        if self.x3 < -150:
            self.x3 = 750
        if self.xl1 < -150:
            self.xl1 = 750
        if self.xl2 < -150:
            self.xl2 = 750
        if self.xl3 < -150:
            self.xl3 = 750

    def draw(self):
        screen.blit(self.b2, (self.x, self.y1))



        screen.blit(self.b4, (self.x2, self.y2))
        screen.blit(self.b5, (self.x3, self.y3))
        screen.blit(self.bl1, (self.xl1, self.yl1))

        screen.blit(self.bl2, (self.xl2, self.yl2))
        screen.blit(self.bl3, (self.xl3, self.yl3))

    def col(self):
        if self.xm-self.x ==5 or self.xm - self.xl1 == 5:
            if self.ym < self.y1+300  or self.ym+64 > self.yl1:
                print("gsg")

                print(self.x,self.xl1)
                return 1
            else:
                return 0

    def col1(self):
        if self.xm - self.x2 == 5 or self.xm - self.xl2 == 5:
            if self.ym < self.y2 + 256 or self.ym > self.yl2 - 64:
                print("gsg")
                return 1

            else:
                return 0

    def col2(self):
        if self.xm - self.x3 == 5 or self.xm - self.xl3 == 5:
            if self.ym < self.y3 + 256 or self.ym > self.yl3 - 64:
                print("gsg")
                return 1

            else:
                return 0


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
def dd(screen,bird,pipe,back,c):



    back.draw()
    c1 = font.render("Score :" + str(c), True, (255, 255, 255))
    screen.blit(c1, (10, 10))

    for u in pipe:
        u.draw()
    for i in bird:
        i.draw()
    c1 = font.render("Gen :" + str(h), True, (255, 255, 255))
    screen.blit(c1, (700, 15))
    pygame.display.update()


def main(genomes, config):

    nets = []
    ge = []
    bird = []
    c=0
    global h
    h+=1


    for _, g in genomes:
        net = neat.nn.FeedForwardNetwork.create(g, config)
        nets.append(net)
        bird.append(birds(30, 100))

        g.fitness = 0
        ge.append(g)
    back = background(0, -700)
    pipe = [pipes(600, 900, 1200, 600, 900, 1200,30,100)]
    r = True
    while run and len(bird)>0:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                r = False
                pygame.quit()


        for v, j in enumerate(bird):
               j.move()
               ge[v].fitness +=0.1

               output1=nets[v].activate((j.ym,abs(j.ym-pipe[0].y1+256),abs(j.ym-pipe[0].yl1)))
               output2 = nets[v].activate((j.ym, abs(j.ym - pipe[0].y2+256), abs(j.ym - pipe[0].yl2)))
               output3= nets[v].activate((j.ym, abs(j.ym - pipe[0].y3+256), abs(j.ym - pipe[0].yl3)))

               if output1[0] >0.5 or output2[0] >0.5 or output3[0]>0.5:
                    j.jump()

        for i in pipe:
            i.move()
            for j in enumerate(bird):
               co=i.col()
               co1 = i.col1()
               co2 = i.col2()
               if co:
                   print("k")
                   bird.pop()


               elif co1:
                   print("k")
                   ge[v].fitness -=10
                   bird.pop()

               elif co2:
                   print("k")
                   ge[v].fitness -=10
                   bird.pop()

        for v, j in enumerate(bird):
            if j.ym+26 >550 or j.ym <10:
                ge[v].fitness -= 5
                bird.pop(v)
                nets.pop(v)
                ge.pop(v)
        back.move()
        dd(screen, bird, pipe, back, c)





def run(config_path):
    config = neat.config.Config(neat.DefaultGenome, neat.DefaultReproduction, neat.DefaultSpeciesSet,
                                neat.DefaultStagnation, config_path)
    p = neat.Population(config)
    p.add_reporter(neat.StdOutReporter(True))
    stats = neat.StatisticsReporter()
    p.add_reporter(stats)
    winner = p.run(main, 50)


if __name__ == "__main__":
    local_dir = os.path.dirname(__file__)
    config_path = os.path.join(local_dir, "Untitled Document 1.txt ")
    run(config_path)

