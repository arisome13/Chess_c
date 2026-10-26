
#include <gtk/gtk.h>
#include "type.h"
#include "userint.h"

/* 0 = empty; uppercase = white, lowercase = black */
static char UI_charboard[8][8];
/* selected square or NULL */
static Square_T UI_selected = NULL;
/* buttons show on the ui window */
static GtkWidget *UI_buttons[8][8];
/* function to call when a second square is hit */
static SendMove_func sendfunc = NULL;
/* host gui window */
static GtkWidget *UI_window = NULL;

static const char *CSS = (
    ".square {  min-width: 64px; min-height: 64px;  padding: 0; border-radius: 0; border: none; box-shadow: none; background-image: none; font-size: 40px; color: #000;}"
    ".light    { background-color: #f0d9b5; }"
    ".dark     { background-color: #b58863; }"
    //".selected { background-color: #f6f669; }"
    //".moved    { background-color: #f5d797; }"
    ".selected { background-image: linear-gradient(rgba(246, 246, 105, 0.6), rgba(246, 246, 105, 0.6)); }"
    ".moved    { background-image: linear-gradient(rgba(246, 246, 105, 0.45), rgba(246, 246, 105, 0.45)); }"
);

/* ... */
static void clear_selection(void)
{
    if (UI_selected != NULL) {
        Square_free(UI_selected);
        UI_selected = NULL;
    }
}
/* Sync every button with the board array and selection. */
static void refresh(void)
{
    // if the buttons don't exist, don't refresh
    if (UI_window == NULL)
        return;
        
    for (size_t r = 0; r < 8; r++) {
    for (size_t c = 0; c < 8; c++) {
        GtkWidget *btn = UI_buttons[r][c];

        gtk_button_set_label(GTK_BUTTON(btn), 
            UI_charboard[r][c] ? /* label => */ Type_nameToSymbol(UI_charboard[r][c]) : "");

        if (UI_selected != NULL && r == UI_selected->y && c == UI_selected->x)
            gtk_widget_add_css_class(btn, "selected");
        else
            gtk_widget_remove_css_class(btn, "selected");
        
        //gtk_widget_remove_css_class(btn, "moved");
    }}
}
/* ... */
static void on_square_clicked(GtkButton *button, gpointer user_data)
{
    (void)button;
    int idx = GPOINTER_TO_INT(user_data);
    CHECK_COORDS(idx / 8, idx % 8);
    size_t r = idx / 8, c = idx % 8;

    if (UI_selected == NULL) {// first click
        if (UI_charboard[r][c])
            UI_selected = Square_newCoords(r, c);
    } else { // second click
        size_t fromY = UI_selected->y, fromX = UI_selected->x;
        clear_selection();
        if (sendfunc && !(fromY == r && fromX == c))
            sendfunc(fromY, fromX, r, c);
    }
    refresh();
}
/* ... */
static void activate(GtkApplication *gtk_app, gpointer user_data)
{
    (void)user_data;
    if (UI_window != NULL) {
        gtk_window_present(GTK_WINDOW(UI_window));
        return;
    }

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

    char startingboard[8][8] = {
        {'r','n','b','q','k','b','n','r'},
        {'p','p','p','p','p','p','p','p'},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {'P','P','P','P','P','P','P','P'},
        {'R','N','B','Q','K','B','N','R'},
    };

    for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 8; c++) {
        GtkWidget *btn = gtk_button_new();

        gtk_widget_add_css_class(btn, "square");
        gtk_widget_add_css_class(btn, (r + c) % 2 == 0 ? "light" : "dark");
        gtk_widget_set_focusable(btn, FALSE);

        g_signal_connect(btn, "clicked", // when clicked...
            G_CALLBACK(on_square_clicked), // ... this function is called
            GINT_TO_POINTER(r * 8 + c)); // ... and this information is passed

        gtk_grid_attach(GTK_GRID(grid), btn, c, r, 1, 1);
        UI_buttons[r][c] = btn;
        UI_charboard[r][c] = startingboard[r][c];
    }}

    gtk_window_set_child(GTK_WINDOW(window), grid);
    UI_window = window;
    refresh();
    gtk_window_present(GTK_WINDOW(window));
}

void ChessUI_load(CharBoard inputboard, Square_T s1, Square_T s2)
{
    // set the board up
    for (size_t y = 0; y < 8; y++) {
    for (size_t x = 0; x < 8; x++) {
        UI_charboard[y][x] = inputboard[y][x] == ' ' ? 0 : inputboard[y][x];
        gtk_widget_remove_css_class(UI_buttons[y][x], "moved");
        if (s1 != NULL && s2 != NULL)
            if ((y == s1->y && x == s1->x) || (y == s2->y && x == s2->x))
                gtk_widget_add_css_class(UI_buttons[y][x], "moved");
    }}

    clear_selection();
    refresh();
}
void ChessUI_run(SendMove_func sfunc)
{
    sendfunc = sfunc;

    GtkApplication *gtk_app =
        gtk_application_new("org.example.ChessBoard", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(gtk_app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(gtk_app), 0, 0);
    (void)status;

    g_object_unref(gtk_app);
    UI_window = NULL;
    clear_selection();
}
