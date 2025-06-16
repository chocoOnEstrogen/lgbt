#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

// Version string (defined by Makefile)
#ifndef VERSION
#define VERSION "0.0.0"
#endif

#define MAX_WIDTH 128
#define MAX_HEIGHT 128
#define MAX_FLAGS 32
#define MAX_COLORS 16
#define MAX_FLAG_NAME 32
#define MAX_ERROR_MSG 256

typedef struct {
    const char *name;
    int stripe_count;
    const char *colors[8];
    const char *description;
} Flag;

// Extended ANSI color codes
const char *ansi_colors[] = {
    "\x1b[48;5;15m ", // white
    "\x1b[48;5;218m ", // pink
    "\x1b[48;5;39m ",  // blue
    "\x1b[48;5;165m ", // magenta
    "\x1b[48;5;196m ", // red
    "\x1b[48;5;226m ", // yellow
    "\x1b[48;5;46m ",  // green
    "\x1b[48;5;0m ",   // black
    "\x1b[48;5;208m ", // orange
    "\x1b[48;5;93m ",  // purple
    "\x1b[48;5;51m ",  // cyan
    "\x1b[48;5;172m ", // brown
    "\x1b[48;5;240m ", // gray
    "\x1b[48;5;226m ", // gold
    "\x1b[48;5;201m ", // hot pink
    "\x1b[48;5;231m ", // bright white
    "\x1b[48;5;199m ", // bright magenta
    "\x1b[48;5;213m ", // light pink
    "\x1b[48;5;147m ", // light purple
    "\x1b[48;5;159m ", // light cyan
    "\x1b[48;5;229m ", // light yellow
    "\x1b[48;5;193m ", // light green
    "\x1b[48;5;209m ", // light orange
    "\x1b[48;5;255m "  // bright gray
};

// Extended flag definitions
Flag flags[] = {
    {
        "trans", 5,
        {"blue", "pink", "white", "pink", "blue"},
        "Transgender Pride Flag - Represents the transgender community with blue and pink stripes for traditional gender colors and white for those who are transitioning or non-binary"
    },
    {
        "lesbian", 7,
        {"red", "red", "magenta", "white", "magenta", "magenta", "red"},
        "Lesbian Pride Flag - Features shades of red and pink representing love and femininity, with white for unique relationships to womanhood"
    },
    {
        "rainbow", 6,
        {"red", "orange", "yellow", "green", "blue", "magenta"},
        "Rainbow Pride Flag - The universal symbol of LGBTQ+ pride, representing diversity and inclusivity across the community"
    },
    {
        "bi", 3,
        {"magenta", "purple", "blue"},
        "Bisexual Pride Flag - Magenta for same-gender attraction, blue for different-gender attraction, and purple for attraction to both"
    },
    {
        "pan", 3,
        {"magenta", "yellow", "cyan"},
        "Pansexual Pride Flag - Represents attraction to all genders, with magenta for women, yellow for non-binary people, and cyan for men"
    },
    {
        "nonbinary", 4,
        {"yellow", "white", "purple", "black"},
        "Non-binary Pride Flag - Yellow for gender outside the binary, white for many or all genders, purple for those who feel both binary and non-binary, black for agender"
    },
    {
        "ace", 4,
        {"black", "gray", "white", "purple"},
        "Asexual Pride Flag - Black for asexuality, gray for gray-asexuality, white for allies, and purple for community"
    },
    {
        "genderfluid", 5,
        {"pink", "white", "purple", "black", "blue"},
        "Genderfluid Pride Flag - Pink for femininity, blue for masculinity, purple for both, black for all genders, and white for lack of gender"
    },
    {
        "genderqueer", 3,
        {"purple", "white", "green"},
        "Genderqueer Pride Flag - Purple for androgyny, white for agender identity, and green for non-binary identities"
    },
    {
        "intersex", 2,
        {"yellow", "purple"},
        "Intersex Pride Flag - Yellow and purple represent the intersex community, with the circle symbolizing wholeness and completeness"
    },
    {
        "aromantic", 5,
        {"green", "lightgreen", "white", "gray", "black"},
        "Aromantic Pride Flag - Green for aromanticism, light green for the aromantic spectrum, white for platonic love, gray for gray-aromanticism, and black for alloromantic allies"
    },
    {
        "demisexual", 4,
        {"black", "gray", "white", "purple"},
        "Demisexual Pride Flag - Black for asexuality, gray for demisexuality, white for sexuality, and purple for community"
    },
    {
        "agender", 7,
        {"black", "gray", "white", "lightgreen", "white", "gray", "black"},
        "Agender Pride Flag - Black and white for absence of gender, gray for semi-genderlessness, and green for non-binary identities"
    },
    {
        "polyamorous", 3,
        {"blue", "red", "black"},
        "Polyamorous Pride Flag - Blue for openness and honesty, red for love and passion, and black for solidarity with those who must hide their polyamorous relationships"
    }
};

// Error handling
typedef enum {
    ERR_NONE = 0,
    ERR_NO_FLAG,
    ERR_INVALID_FLAG,
    ERR_INVALID_DIMENSIONS,
    ERR_INVALID_MATRIX_FORMAT,
    ERR_INVALID_ARGUMENT
} ErrorCode;

const char *error_messages[] = {
    "No error",
    "No flag specified",
    "Invalid flag name",
    "Invalid dimensions",
    "Invalid matrix format",
    "Invalid argument"
};

void print_error(ErrorCode code, const char *details) {
    char message[MAX_ERROR_MSG];
    if (details) {
        snprintf(message, sizeof(message) - 1, "%s: %s", error_messages[code], details);
    } else {
        strncpy(message, error_messages[code], sizeof(message) - 1);
        message[sizeof(message) - 1] = '\0';  // Ensure null termination
    }
    fprintf(stderr, "Error: %s\n", message);
}

const char *get_ansi_color(const char *color_name) {
    const char *color_map[][2] = {
        {"white", ansi_colors[0]},
        {"pink", ansi_colors[1]},
        {"blue", ansi_colors[2]},
        {"magenta", ansi_colors[3]},
        {"red", ansi_colors[4]},
        {"yellow", ansi_colors[5]},
        {"green", ansi_colors[6]},
        {"black", ansi_colors[7]},
        {"orange", ansi_colors[8]},
        {"purple", ansi_colors[9]},
        {"cyan", ansi_colors[10]},
        {"brown", ansi_colors[11]},
        {"gray", ansi_colors[12]},
        {"gold", ansi_colors[13]},
        {"hotpink", ansi_colors[14]},
        {"brightwhite", ansi_colors[15]},
        {"brightmagenta", ansi_colors[16]},
        {"lightpink", ansi_colors[17]},
        {"lightpurple", ansi_colors[18]},
        {"lightcyan", ansi_colors[19]},
        {"lightyellow", ansi_colors[20]},
        {"lightgreen", ansi_colors[21]},
        {"lightorange", ansi_colors[22]},
        {"brightgray", ansi_colors[23]},
        {NULL, NULL}
    };

    for (int i = 0; color_map[i][0] != NULL; i++) {
        if (strcmp(color_name, color_map[i][0]) == 0) {
            return color_map[i][1];
        }
    }
    return ansi_colors[0]; // Default to white if color not found
}

Flag *find_flag(const char *name) {
    for (size_t i = 0; i < sizeof(flags)/sizeof(flags[0]); i++) {
        if (strcmp(flags[i].name, name) == 0) {
            return &flags[i];
        }
    }
    return NULL;
}

void print_help(const char *program_name) {
    printf("\nUsage: %s --flag=FLAGNAME [OPTIONS]\n", program_name);
    printf("Version: %s\n\n", VERSION);
    printf("Options:\n");
    printf("  --flag=FLAGNAME      Show the specified pride flag.\n");
    printf("  --matrix=WxH         Set the flag width and height (default: 32x16).\n");
    printf("  --border             Draw a border around the flag.\n");
    printf("  --reverse            Reverse the order of the flag's stripes.\n");
    printf("  --list               List all available flags and descriptions.\n");
    printf("  --help               Show this help message.\n");
    printf("  --version            Show version information.\n");
    printf("\nExamples:\n");
    printf("  %s --flag=trans\n", program_name);
    printf("  %s --flag=lesbian --matrix=40x20 --border\n", program_name);
    printf("  %s --flag=rainbow --reverse\n", program_name);
    printf("  %s --list\n", program_name);
    printf("\nAvailable flags:\n");
    printf("  trans        - Transgender Pride Flag\n");
    printf("  lesbian      - Lesbian Pride Flag\n");
    printf("  rainbow      - Rainbow Pride Flag\n");
    printf("  bi           - Bisexual Pride Flag\n");
    printf("  pan          - Pansexual Pride Flag\n");
    printf("  nonbinary    - Non-binary Pride Flag\n");
    printf("  ace          - Asexual Pride Flag\n");
    printf("  genderfluid  - Genderfluid Pride Flag\n");
    printf("  genderqueer  - Genderqueer Pride Flag\n");
    printf("  intersex     - Intersex Pride Flag\n");
    printf("  aromantic    - Aromantic Pride Flag\n");
    printf("  demisexual   - Demisexual Pride Flag\n");
    printf("  agender      - Agender Pride Flag\n");
    printf("  polyamorous  - Polyamorous Pride Flag\n");
    printf("\nTips:\n");
    printf("  - Use --list for detailed flag descriptions\n");
    printf("  - Maximum dimensions are %dx%d\n", MAX_WIDTH, MAX_HEIGHT);
    printf("  - For best results, use a terminal that supports 256 colors\n");
    printf("  - Use a monospace font for proper display\n");
    printf("\n");
}

void print_flag_list() {
    printf("Available flags:\n");
    for (size_t i = 0; i < sizeof(flags)/sizeof(flags[0]); i++) {
        printf("  %-12s - %s\n", flags[i].name, flags[i].description);
    }
    printf("\nUse --flag=NAME to display a specific flag.\n");
    printf("Example: lgbt --flag=trans --border --matrix=40x20\n");
}

void draw_flag(Flag *flag, int width, int height, int border, int reverse) {
    if (!flag || width <= 0 || height <= 0) return;
    
    // Calculate dimensions
    int stripe_height = height / flag->stripe_count;
    int remaining_height = height % flag->stripe_count;
    int y = 0;
    int border_offset = border ? 1 : 0;
    int content_width = width - 2 * border_offset;
    
    // Border characters
    const char *border_chars[] = {
        "+", "-", "|", "+", "-", "|"  // top-left, top, top-right, bottom-left, bottom, bottom-right
    };
    
    // Reset terminal colors
    printf("\x1b[0m");
    
    if (border) {
        // Top border
        printf("%s", border_chars[0]);
        for (int i = 0; i < width - 2; i++) printf("%s", border_chars[1]);
        printf("%s\n", border_chars[2]);
    }
    
    // Calculate stripe indices
    int stripe_indices[8];
    for (int i = 0; i < flag->stripe_count; i++) {
        stripe_indices[i] = reverse ? (flag->stripe_count - 1 - i) : i;
    }
    
    // Draw stripes
    for (int i = 0; i < flag->stripe_count; i++) {
        const char *color = get_ansi_color(flag->colors[stripe_indices[i]]);
        int current_stripe_height = stripe_height + (remaining_height > 0 ? 1 : 0);
        remaining_height--;
        
        for (int h = 0; h < current_stripe_height; h++, y++) {
            if (border) printf("%s", border_chars[3]);
            
            // Draw the stripe
            for (int x = 0; x < content_width; x++) {
                printf("%s", color);
            }
            
            if (border) printf("%s\x1b[0m", border_chars[3]);
            printf("\x1b[0m\n");
        }
    }
    
    if (border) {
        // Bottom border
        printf("%s", border_chars[4]);
        for (int i = 0; i < width - 2; i++) printf("%s", border_chars[1]);
        printf("%s\n", border_chars[5]);
    }
    
    // Reset terminal colors again
    printf("\x1b[0m");
}

int validate_dimensions(int width, int height) {
    if (width <= 0 || height <= 0) {
        print_error(ERR_INVALID_DIMENSIONS, "Dimensions must be positive");
        return 0;
    }
    if (width > MAX_WIDTH || height > MAX_HEIGHT) {
        char details[MAX_ERROR_MSG];
        snprintf(details, sizeof(details), "Dimensions exceed maximum (%dx%d). Clamping to maximum.", 
                MAX_WIDTH, MAX_HEIGHT);
        print_error(ERR_INVALID_DIMENSIONS, details);
        return 0;
    }
    return 1;
}

int parse_matrix_arg(const char *arg, int *width, int *height) {
    if (sscanf(arg, "%dx%d", width, height) != 2) {
        print_error(ERR_INVALID_MATRIX_FORMAT, "Use WxH format (e.g., 32x16)");
        return 0;
    }
    return validate_dimensions(*width, *height);
}

int main(int argc, char *argv[]) {
    const char *flag_arg = NULL;
    int width = 32, height = 16;
    int border = 0;
    int reverse = 0;
    
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "--flag=", 7) == 0) {
            flag_arg = argv[i] + 7;
            if (strlen(flag_arg) > MAX_FLAG_NAME) {
                print_error(ERR_INVALID_FLAG, "Flag name too long");
                return 1;
            }
        } else if (strncmp(argv[i], "--matrix=", 9) == 0) {
            if (!parse_matrix_arg(argv[i] + 9, &width, &height)) {
                return 1;
            }
        } else if (strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "--version") == 0) {
            printf("LGBT Flag Display Tool version %s\n", VERSION);
            return 0;
        } else if (strcmp(argv[i], "--border") == 0) {
            border = 1;
        } else if (strcmp(argv[i], "--list") == 0) {
            print_flag_list();
            return 0;
        } else if (strcmp(argv[i], "--reverse") == 0) {
            reverse = 1;
        } else {
            char details[MAX_ERROR_MSG];
            snprintf(details, sizeof(details), "Unknown argument: %s", argv[i]);
            print_error(ERR_INVALID_ARGUMENT, details);
            print_help(argv[0]);
            return 1;
        }
    }
    
    // Validate required arguments
    if (!flag_arg) {
        print_error(ERR_NO_FLAG, NULL);
        print_help(argv[0]);
        return 1;
    }
    
    // Find and validate flag
    Flag *flag = find_flag(flag_arg);
    if (!flag) {
        char details[MAX_ERROR_MSG];
        snprintf(details, sizeof(details), "Flag not found: %s", flag_arg);
        print_error(ERR_INVALID_FLAG, details);
        return 1;
    }
    
    // Draw the flag
    draw_flag(flag, width, height, border, reverse);
    return 0;
}
