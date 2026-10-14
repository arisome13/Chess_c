/*
 * Minimal GTK4 chess board in C.
 *
 * Build:  gcc chessboard.c -o chessboard $(pkg-config --cflags --libs gtk4)
 * Run:    ./chessboard
 */
#include <gtk/gtk.h>

typedef struct App App;

typedef struct {
    App *app;
    int row, col;
} Square;

struct App {
    char       board[8][8];    /* 0 = empty; uppercase = white, lowercase = black */
    int        sel_r, sel_c;   /* selected square, or -1 */
    GtkWidget *buttons[8][8];
    Square     squares[8][8];  /* user data passed to the click handler */
};

static const char *CSS =
    ".square {"
    "  min-width: 64px; min-height: 64px;"
    "  padding: 0; border-radius: 0; border: none;"
    "  box-shadow: none; background-image: none;"
    "  font-size: 40px; color: #000;"
    "}"
    ".light    { background-color: #f0d9b5; }"
    ".dark     { background-color: #b58863; }"
    ".selected { background-color: #f6f669; }";

static const char *glyph_for(char p)
{
    switch (p) {
    case 'K': return "♔"; case 'Q': return "♕"; case 'R': return "♖";
    case 'B': return "♗"; case 'N': return "♘"; case 'P': return "♙";
    case 'k': return "♚"; case 'q': return "♛"; case 'r': return "♜";
    case 'b': return "♝"; case 'n': return "♞"; case 'p': return "♟";
    default:  return "";
    }
}

static void init_position(App *app)
{
    const char *back = "RNBQKBNR";

    memset(app->board, 0, sizeof app->board);
    for (int c = 0; c < 8; c++) {
        app->board[0][c] = g_ascii_tolower(back[c]);  /* black back rank (rank 8) */
        app->board[1][c] = 'p';
        app->board[6][c] = 'P';
        app->board[7][c] = back[c];                   /* white back rank (rank 1) */
    }
    app->sel_r = app->sel_c = -1;
}

/* Sync every button with the board array and selection. */
static void refresh(App *app)
{
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            GtkWidget *btn = app->buttons[r][c];

            gtk_button_set_label(GTK_BUTTON(btn), glyph_for(app->board[r][c]));

            if (r == app->sel_r && c == app->sel_c)
                gtk_widget_add_css_class(btn, "selected");
            else
                gtk_widget_remove_css_class(btn, "selected");
        }
    }
}

static void on_square_clicked(GtkButton *button, gpointer user_data)
{
    Square *sq  = user_data;
    App    *app = sq->app;
    (void)button;

    if (app->sel_r < 0) {
        /* First click: pick up a piece, if there is one. */
        if (app->board[sq->row][sq->col])
            app->sel_r = sq->row, app->sel_c = sq->col;
    } else {
        /* Second click: move (no chess rules enforced). */
        if (app->sel_r != sq->row || app->sel_c != sq->col) {
            app->board[sq->row][sq->col] = app->board[app->sel_r][app->sel_c];
            app->board[app->sel_r][app->sel_c] = 0;
        }
        app->sel_r = app->sel_c = -1;
    }
    refresh(app);
}

static void activate(GtkApplication *gtk_app, gpointer user_data)
{
    App *app = user_data;

    /* Load CSS for the whole display. */
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider, CSS);
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);

    GtkWidget *window = gtk_application_window_new(gtk_app);
    gtk_window_set_title(GTK_WINDOW(window), "GTK Chess Board");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    init_position(app);

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            GtkWidget *btn = gtk_button_new();

            gtk_widget_add_css_class(btn, "square");
            gtk_widget_add_css_class(btn, (r + c) % 2 == 0 ? "light" : "dark");
            gtk_widget_set_focusable(btn, FALSE);

            app->squares[r][c] = (Square){ app, r, c };
            g_signal_connect(btn, "clicked",
                             G_CALLBACK(on_square_clicked), &app->squares[r][c]);

            gtk_grid_attach(GTK_GRID(grid), btn, c, r, 1, 1);
            app->buttons[r][c] = btn;
        }
    }

    gtk_window_set_child(GTK_WINDOW(window), grid);
    refresh(app);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
    static App app;   /* static: must outlive the signal handlers */

    GtkApplication *gtk_app =
        gtk_application_new("org.example.ChessBoard", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(gtk_app, "activate", G_CALLBACK(activate), &app);

    int status = g_application_run(G_APPLICATION(gtk_app), argc, argv);
    g_object_unref(gtk_app);
    return status;
}