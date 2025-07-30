#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // For sleep()

#define MAX_GAMES 1000
#define NAME_LEN 50
#define SCORE_FILE "scoreboard.txt"

typedef struct
{
    char name[NAME_LEN];
    int level;    // 1=Easy, 2=Medium, 3=Hard
    int attempts; // -1 means loss
} Score;

// Load scores from file into array, returns count
int load_scores(Score scores[], int max)
{
    FILE *fp = fopen(SCORE_FILE, "r");
    if (!fp)
        return 0; // no file yet

    int count = 0;
    while (count < max && fscanf(fp, "%49s %d %d", scores[count].name, &scores[count].level, &scores[count].attempts) == 3)
    {
        count++;
    }
    fclose(fp);
    return count;
}

// Save scores array to file
void save_scores(Score scores[], int count)
{
    FILE *fp = fopen(SCORE_FILE, "w");
    if (!fp)
    {
        printf("Error: could not save scoreboard.\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s %d %d\n", scores[i].name, scores[i].level, scores[i].attempts);
    }
    fclose(fp);
}

// Convert level int to string
const char *level_to_str(int level)
{
    switch (level)
    {
    case 1:
        return "Easy";
    case 2:
        return "Medium";
    case 3:
        return "Hard";
    default:
        return "Unknown";
    }
}

// Compare function for sorting scoreboard:
// Wins come before losses
// Among wins, fewer attempts is better
// If tied, sort alphabetically by name
int score_compare(const void *a, const void *b)
{
    const Score *s1 = (const Score *)a;
    const Score *s2 = (const Score *)b;

    // Primary: Sort by level (descending)
    if (s1->level != s2->level)
        return s2->level - s1->level;

    // Secondary: Losses go last
    if (s1->attempts == -1 && s2->attempts != -1)
        return 1;
    if (s1->attempts != -1 && s2->attempts == -1)
        return -1;

    // If both won or both lost: sort by attempts (descending)
    if (s1->attempts != s2->attempts)
        return s2->attempts - s1->attempts;

    // Tertiary: sort by name (ascending)
    return strcmp(s1->name, s2->name);
}

int main()
{
    int random, guess, no_of_guess, max_range = 100, max_attempts = -1;
    char play_again;
    int level;
    char player_name[NAME_LEN];

    Score scoreboard[MAX_GAMES];
    int game_count = 0;

    // Load existing scores
    game_count = load_scores(scoreboard, MAX_GAMES);

    // Get player name once at the start
    printf("To START Game\n");
    printf("Enter your name: ");
    scanf("%49s", player_name);

    srand(time(NULL));

    do
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        printf("===========================================\n");
        printf(" Welcome to the Number Guessing Game!\n");
        printf("===========================================\n");
        printf("Hello, %s!\n", player_name);
        printf("\nSelect Difficulty Level:\n");
        printf("1. Easy   (1-50, Unlimited attempts)\n");
        printf("2. Medium (1-100, Max 10 attempts)\n");
        printf("3. Hard   (1-500, Max 7 attempts)\n");
        printf("Enter choice (1-3): ");
        scanf("%d", &level);

        switch (level)
        {
        case 1:
            max_range = 50;
            max_attempts = -1;
            break;
        case 2:
            max_range = 100;
            max_attempts = 10;
            break;
        case 3:
            max_range = 500;
            max_attempts = 7;
            break;
        default:
            printf("Invalid level. Defaulting to Medium.\n");
            max_range = 100;
            max_attempts = 10;
            level = 2;
            break;
        }

        random = rand() % max_range + 1;
        no_of_guess = 0;
        int won = 0;

        do
        {
            printf("\nGuess a number (1 to %d): ", max_range);
            if (scanf("%d", &guess) != 1)
            {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n')
                    ;
                continue;
            }
            no_of_guess++;
            if (guess < random)
            {
                printf("Too low! Try again.\n");
            }
            else if (guess > random)
            {
                printf("Too high! Try again.\n");
            }
            else
            {
                printf("\n🎉 Correct! You guessed it in %d attempts!\n", no_of_guess);
                won = 1;
                break;
            }
            if (max_attempts != -1 && no_of_guess >= max_attempts)
            {
                printf("\n❌ Game Over! You've used all %d attempts.\n", max_attempts);
                printf("The correct number was: %d\n", random);
                break;
            }
        } while (1);

        // Save current game result in scoreboard array (append)
        if (game_count < MAX_GAMES)
        {
            strncpy(scoreboard[game_count].name, player_name, NAME_LEN - 1);
            scoreboard[game_count].name[NAME_LEN - 1] = '\0';
            scoreboard[game_count].level = level;
            scoreboard[game_count].attempts = won ? no_of_guess : -1;
            game_count++;
        }
        else
        {
            printf("Scoreboard is full, cannot record more games.\n");
        }

        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &play_again);

    } while (play_again == 'y' || play_again == 'Y');

    // Save all scores to file
    save_scores(scoreboard, game_count);

    // Ask if the user wants to see the scoreboard
    char see_scoreboard;
    printf("\nWould you like to see the scoreboard? (y/n): ");
    scanf(" %c", &see_scoreboard);
    if (see_scoreboard == 'y' || see_scoreboard == 'Y')
    {
        // Sort scoreboard before displaying
        qsort(scoreboard, game_count, sizeof(Score), score_compare);

        printf("\n============= SCOREBOARD =============\n");
        printf("No. | Name         | Level   | Attempts\n");
        printf("----+--------------+---------+---------\n");
        for (int i = 0; i < game_count; i++)
        {
            printf("%3d | %-12s | %-7s | ", i + 1, scoreboard[i].name, level_to_str(scoreboard[i].level));
            if (scoreboard[i].attempts == -1)
                printf("Lost\n");
            else
                printf("%d\n", scoreboard[i].attempts);
        }
        printf("=======================================\n");
    }

    printf("Thanks for Playing! Goodbye!\n");
    printf("Developed by: Vamsi T\n");
    return 0;
}
