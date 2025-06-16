# User Guide

This guide explains how to use the LGBT Flag Display Tool effectively.

## Basic Usage

The basic syntax is:

```bash
lgbt --flag=FLAGNAME [OPTIONS]
```

### Displaying Flags

To display a specific flag:

```bash
lgbt --flag=trans
```

### Available Flags

The tool supports the following flags with their meanings:

- `trans` - Transgender Pride Flag - Represents the transgender community with blue and pink stripes for traditional gender colors and white for those who are transitioning or non-binary
- `lesbian` - Lesbian Pride Flag - Features shades of red and pink representing love and femininity, with white for unique relationships to womanhood
- `rainbow` - Rainbow Pride Flag - The universal symbol of LGBTQ+ pride, representing diversity and inclusivity across the community
- `bi` - Bisexual Pride Flag - Magenta for same-gender attraction, blue for different-gender attraction, and purple for attraction to both
- `pan` - Pansexual Pride Flag - Represents attraction to all genders, with magenta for women, yellow for non-binary people, and cyan for men
- `nonbinary` - Non-binary Pride Flag - Yellow for gender outside the binary, white for many or all genders, purple for those who feel both binary and non-binary, black for agender
- `ace` - Asexual Pride Flag - Black for asexuality, gray for gray-asexuality, white for allies, and purple for community
- `genderfluid` - Genderfluid Pride Flag - Pink for femininity, blue for masculinity, purple for both, black for all genders, and white for lack of gender
- `genderqueer` - Genderqueer Pride Flag - Purple for androgyny, white for agender identity, and green for non-binary identities
- `intersex` - Intersex Pride Flag - Yellow and purple represent the intersex community, with the circle symbolizing wholeness and completeness
- `aromantic` - Aromantic Pride Flag - Green for aromanticism, light green for the aromantic spectrum, white for platonic love, gray for gray-aromanticism, and black for alloromantic allies
- `demisexual` - Demisexual Pride Flag - Black for asexuality, gray for demisexuality, white for sexuality, and purple for community
- `agender` - Agender Pride Flag - Black and white for absence of gender, gray for semi-genderlessness, and green for non-binary identities
- `polyamorous` - Polyamorous Pride Flag - Blue for openness and honesty, red for love and passion, and black for solidarity with those who must hide their polyamorous relationships

## Options

### Flag Dimensions

Control the size of the displayed flag:

```bash
lgbt --flag=rainbow --matrix=40x20
```

- Width: 40 characters
- Height: 20 lines
- Maximum dimensions: 128x128 characters

### Border

Add a border around the flag:

```bash
lgbt --flag=lesbian --border
```

### Reverse Display

Display the flag in reverse order:

```bash
lgbt --flag=bi --reverse
```

### List Available Flags

View all available flags and their descriptions:

```bash
lgbt --list
```

### Help

Display help information:

```bash
lgbt --help
```

## Examples

### Basic Examples

```bash
# Display transgender flag
lgbt --flag=trans

# Display rainbow flag with border
lgbt --flag=rainbow --border

# Display lesbian flag in reverse
lgbt --flag=lesbian --reverse
```

### Advanced Examples

```bash
# Large rainbow flag with border
lgbt --flag=rainbow --matrix=60x30 --border

# Small pansexual flag
lgbt --flag=pan --matrix=20x10

# Reversed non-binary flag with border
lgbt --flag=nonbinary --reverse --border
```

## Tips and Tricks

1. **Terminal Size**: Ensure your terminal window is large enough to display the flag at your chosen dimensions.

2. **Color Support**: The tool uses ANSI color codes. For best results:
   - Use a terminal that supports 256 colors
   - Use a terminal with good color rendering
   - Consider using a dark theme for better contrast

3. **Combining Options**: You can combine multiple options:
   ```bash
   lgbt --flag=rainbow --matrix=40x20 --border --reverse
   ```

4. **Custom Dimensions**: The maximum dimensions are 128x128 characters. The tool will automatically clamp larger values.

5. **Flag Meanings**: Use `--list` to see detailed descriptions of each flag's meaning and symbolism.

## Troubleshooting

### Color Issues

If colors don't display correctly:
- Ensure your terminal supports ANSI colors
- Try a different terminal emulator
- Check your terminal's color settings
- Verify your terminal supports 256 colors

### Display Problems

If the flag doesn't display properly:
- Check if your terminal window is large enough
- Try reducing the dimensions
- Ensure you're using a monospace font
- Verify your terminal's character width settings

### Command Not Found

If the `lgbt` command isn't found:
- Verify the installation was successful
- Check if the binary is in your PATH
- Try using the full path to the binary
- Reinstall the tool if necessary 