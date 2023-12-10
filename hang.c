#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <SDL2/SDL.h>

const char *options_fruits[] = {"Apple", "Blueberry", "Mandarin", "Pineapple", "Pomegranate", "Watermelon"};
const char *options_animals[] = {"Hedgehog", "Rhinoceros", "Squirrel", "Panther", "Walrus", "Zebra"};
const char *options_countries[] = {"India", "Hungary", "Kyrgyzstan", "Switzerland", "Zimbabwe", "Dominica"};

int winCount = 0;
int count = 0;

char chosenWord[50];

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void drawHangman(int count) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Set color to black

    switch (count) {
        case 1:  // Head
            SDL_RenderDrawCircle(renderer, 200, 100, 20);
            break;
        case 2:  // Body
            SDL_RenderDrawLine(renderer, 200, 120, 200, 180);
            break;
        case 3:  // Left Arm
            SDL_RenderDrawLine(renderer, 200, 130, 180, 160);
            break;
        case 4:  // Right Arm
            SDL_RenderDrawLine(renderer, 200, 130, 220, 160);
            break;
        case 5:  // Left Leg
            SDL_RenderDrawLine(renderer, 200, 180, 180, 220);
            break;
        case 6:  // Right Leg
            SDL_RenderDrawLine(renderer, 200, 180, 220, 220);
            break;
    }

    SDL_RenderPresent(renderer);
}

void displayOptions() {
    printf("Please Select An Option\n");

    printf("Fruits: ");
    for (int i = 0; i < sizeof(options_fruits) / sizeof(options_fruits[0]); i++) {
        printf("%s ", options_fruits[i]);
    }
    printf("\n");

    printf("Animals: ");
    for (int i = 0; i < sizeof(options_animals) / sizeof(options_animals[0]); i++) {
        printf("%s ", options_animals[i]);
    }
    printf("\n");

    printf("Countries: ");
    for (int i = 0; i < sizeof(options_countries) / sizeof(options_countries[0]); i++) {
        printf("%s ", options_countries[i]);
    }
    printf("\n");
}

void generateWord(const char *optionValue) {
    if (strcmp(optionValue, "fruits") == 0) {
        strcpy(chosenWord, options_fruits[rand() % (sizeof(options_fruits) / sizeof(options_fruits[0]))]);
    } else if (strcmp(optionValue, "animals") == 0) {
        strcpy(chosenWord, options_animals[rand() % (sizeof(options_animals) / sizeof(options_animals[0]))]);
    } else if (strcmp(optionValue, "countries") == 0) {
        strcpy(chosenWord, options_countries[rand() % (sizeof(options_countries) / sizeof(options_countries[0]))]);
    }

    for (int i = 0; chosenWord[i]; i++) {
        chosenWord[i] = toupper(chosenWord[i]);
    }

    for (int i = 0; chosenWord[i]; i++) {
        if (isalpha(chosenWord[i])) {
            printf("_ ");
        } else {
            printf("%c ", chosenWord[i]);
        }
    }
    printf("\n");
}

void initializer() {
    winCount = 0;
    count = 0;

    printf("Please Select A New Game\n");

    displayOptions();
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Hangman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 300, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    srand(time(NULL));

    initializer();

    char optionValue[20];

    while (1) {
        printf("Enter your choice: ");
        scanf("%s", optionValue);

        if (strcmp(optionValue, "fruits") == 0 || strcmp(optionValue, "animals") == 0 || strcmp(optionValue, "countries") == 0) {
            break;
        } else {
            printf("Invalid option. Please enter a valid option.\n");
        }
    }

    generateWord(optionValue);

    // Game loop
    while (1) {
        // Handle user input and update game state

        // Example: Press 'q' to quit
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }

        // Example: Press 'n' for a new game
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_N]) {
            initializer();
            generateWord(optionValue);
        }

        // Example: Press a key to guess a letter
        for (int i = 0; i < 26; ++i) {
            if (state[SDL_SCANCODE_A + i]) {
                // Implement letter guessing logic here
                // ...

                // Example: Draw the hangman based on the count
                drawHangman(count);
            }
        }

        // Check game over conditions and update display
        // ...

        SDL_Delay(16);  // Cap the frame rate
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
