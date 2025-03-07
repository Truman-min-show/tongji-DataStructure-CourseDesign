import pygame
from random import randint
from time import time
from algs import algorithmsDict
import display as display




def main():
    numbers = []
    running = True
    display.algorithmBox.add_options(list(algorithmsDict.keys()))

    alg_iterator = None

    timer_delay = time()
    
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            elif event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE and display.do_sorting:
                display.paused = not display.paused
                display.timer_space_bar = time()

            display.updateWidgets(event)

        display.delay = (display.delayBox.value-display.delayBox.rect.x-6)/1000

        if display.playButton.isActive: 
            display.playButton.isActive = False
            display.do_sorting = True
            current_alg = display.algorithmBox.get_active_option()
            display.numBars = int(display.sizeBox.text)
            numbers = [randint(10, 400) for i in range(display.numBars)] 
            alg_iterator = algorithmsDict[current_alg](numbers, 0, display.numBars-1) 
        if display.stopButton.isActive: 
            display.stopButton.isActive = False
            display.do_sorting = False
            display.paused = False
            try: 
                while True:
                    numbers, redBar1, redBar2, blueBar1, blueBar2 = next(alg_iterator)
            except StopIteration:
                pass

        if display.do_sorting and not display.paused: 
            try:
                if time()-timer_delay >= display.delay:
                    numbers, redBar1, redBar2, blueBar1, blueBar2 = next(alg_iterator)
                    display.drawInterface(numbers, redBar1, redBar2, blueBar1, blueBar2)
                    timer_delay = time()
            except StopIteration:
                display.do_sorting = False
        elif display.do_sorting and display.paused: 
            display.drawInterface(numbers, -1, -1, -1, -1)
        else: 
            a_set = set(range(display.numBars))
            display.drawInterface(numbers, -1, -1, -1, -1, greenRows=a_set)




if __name__ == '__main__':
    main()
