#include "raylib.h"
#include "linked_list.h"
#include "fourier.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 1000
#define HEIGHT 800

// Max length of the drawing path for simplicity
#define MAX_PATH_LEN 2048 

/**
 * Raylib coordinates go from (0, 0) to (WIDTH, HEIGHT) (top left corner to bottom right corner).
 * The y coordinate goes down when increasing y, contrary to the standard 2D plane.
 * 
 * Converts a Raylib point into a standard 2D plane point.
 */
Vector2 raylib_to_plane(Vector2 p) {
    Vector2 p2;
    p2.x = p.x - WIDTH / 2;
    p2.y = -1 * (p.y - HEIGHT / 2);
    return p2;
}

/**
 * Raylib coordinates go from (0, 0) to (WIDTH, HEIGHT) (top left corner to bottom right corner).
 * The y coordinate goes down when increasing y, contrary to the standard 2D plane.
 * 
 * Converts a standard 2D plane point into a Raylib point.
 */
Vector2 plane_to_raylib(Vector2 p) {
    Vector2 p2;
    p2.x = p.x + WIDTH / 2;
    p2.y = -p.y + HEIGHT / 2;
    return p2;
}

/**
 * The points that represent a drawing are stored in a linked list.
 * Draw the lines between the drawing points. 
 */
void draw_points(List point_list) {
    if (!point_list) return;

    Node* aux = point_list;

    while (aux->next != NULL) {
        DrawLineEx(aux->elem, aux->next->elem, 3, BLACK);
        aux = aux->next;
    }
}

/**
 * Converts the points of a given drawing into complex points in order to perform the DFT.
 */
Complex* convert_drawing_to_complex(List point_list, int* N) {
    if (!point_list) return NULL;
    
    *N = 0;
    Node* aux = point_list;
    while (aux != NULL) {
        (*N)++;
        aux = aux->next;
    }
    
    if (*N == 0) return NULL;
    
    Complex* points = (Complex *)malloc(*N * sizeof(Complex));
    if (!points) return NULL;
    
    int i = 0;
    aux = point_list;
    while (aux != NULL && i < *N) {
        Vector2 norm_p = raylib_to_plane(aux->elem);
        points[i].x = norm_p.x;
        points[i].y = norm_p.y;
        
        i++;
        aux = aux->next;
    }
    
    return points;
}

/**
 * Draws the user defined drawing with epicycles using the Fourier coefficients got after performing the DFT with the points.
 * It will continuously draw the path until the user resets the animation.
 */
void draw_epicycles(FourierCoeff* coeffs, int N, bool reset_animation) {
    static float time = 0.0f;
    static Vector2 path[MAX_PATH_LEN];
    static int path_len = 0;

    if (reset_animation) {
        time = 0.0f;
        path_len = 0;
    }

    Vector2 center = { 0.0f, 0.0f };

    for (int i = 0; i < N; i++) {
        Vector2 prev_center = { center.x, center.y };

        float frequency = coeffs[i].frequency;
        float amplitude = coeffs[i].amplitude;
        float phase = coeffs[i].phase;

        center.x += amplitude * cosf(frequency * time + phase);
        center.y += amplitude * sinf(frequency * time + phase);

        DrawCircleLinesV(plane_to_raylib(prev_center), amplitude, GRAY);
        DrawLineV(plane_to_raylib(prev_center), plane_to_raylib(center), BLUE);
    }

    if (path_len < MAX_PATH_LEN) {
        path[path_len] = plane_to_raylib(center);
        path_len++;
    }

    for (int i = 0; i < path_len - 1; i++) {
        DrawLineEx(path[i], path[i+1], 3, RED);
    }
    
    time += 2*PI / N;

    // A full rotation of a circle goes from 0 to 2π radians. The animation loops periodically.
    if (time > 2*PI) { 
        time = 0.0f;
        path_len = 0;
    }
}

int main() {
    // Initialization
    List point_list;
    init_list(&point_list);

    Complex* points = NULL;
    FourierCoeff* coeffs = NULL;
    int N = 0;

    bool show_fourier = false;
    bool show_points = true;
    bool reset_animation = false;

    InitWindow(WIDTH, HEIGHT, "Drawing with Epicycles");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update
        Vector2 mouse_pos = GetMousePosition();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !contains(point_list, mouse_pos) && show_points) {
            append(&point_list, mouse_pos);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && show_points) {
            if (points) free(points);
            if (coeffs) free(coeffs);

            points = convert_drawing_to_complex(point_list, &N);
            if (points && N > 0) {
                coeffs = DFT(points, N);
                show_fourier = true;
                show_points = false;
                reset_animation = true;
            }
        }

        if (IsKeyPressed(KEY_R)) {
            free_list(&point_list);
            if (points) {
                free(points);
                points = NULL;
            }
            if (coeffs) {
                free(coeffs);
                coeffs = NULL;
            }
            N = 0;
            show_fourier = false;
            show_points = true;
            reset_animation = true;
        }

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hold left click to draw. Release when finished. Press R to reset.", 10, 10, 20, DARKGREEN);
            DrawLine(0, HEIGHT / 2, WIDTH, HEIGHT / 2, BLACK);
            DrawLine(WIDTH / 2, 0, WIDTH / 2, HEIGHT, BLACK);

            if (show_fourier) {
                draw_epicycles(coeffs, N, reset_animation);
                reset_animation = false;
            } 
            if (show_points)
                draw_points(point_list);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();
    free_list(&point_list);
    if (points) free(points);
    if (coeffs) free(coeffs);

    return 0;
}