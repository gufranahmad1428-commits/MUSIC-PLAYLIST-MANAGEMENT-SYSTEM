#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Song Node structure
typedef struct Song {
    char title[100];
    char artist[100];
    struct Song* prev;
    struct Song* next;
} Song;

Song* head = NULL;
Song* current = NULL;

// Function to create a new song node
Song* createSong(char* title, char* artist) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    newSong->prev = NULL;
    newSong->next = NULL;
    return newSong;
}

// 1. Add song to playlist (at the end)
void addSong(char* title, char* artist) {
    Song* newSong = createSong(title, artist);
    if (head == NULL) {
        head = newSong;
        current = head;
    } else {
        Song* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newSong;
        newSong->prev = temp;
    }
    printf(">> Added: '%s' by %s\n", title, artist);
}

// 2. Delete song by title
void deleteSong(char* title) {
    if (head == NULL) {
        printf("Playlist is empty!\n");
        return;
    }

    Song* temp = head;
    while (temp != NULL && strcmp(temp->title, title) != 0) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Song '%s' not found.\n", title);
        return;
    }

    // Adjust current pointer if deleting currently playing song
    if (current == temp) {
        if (temp->next != NULL) current = temp->next;
        else current = temp->prev;
    }

    // Node deletion logic
    if (temp == head) {
        head = temp->next;
        if (head != NULL) head->prev = NULL;
    } else {
        temp->prev->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
    }

    free(temp);
    printf(">> Deleted: '%s'\n", title);
}

// 3. Play next song
void playNext() {
    if (current == NULL) {
        printf("Playlist is empty!\n");
        return;
    }
    if (current->next != NULL) {
        current = current->next;
        printf(">> Playing Next: %s - %s\n", current->title, current->artist);
    } else {
        printf("End of playlist reached!\n");
    }
}

// 4. Play previous song
void playPrev() {
    if (current == NULL) {
        printf("Playlist is empty!\n");
        return;
    }
    if (current->prev != NULL) {
        current = current->prev;
        printf(">> Playing Previous: %s - %s\n", current->title, current->artist);
    } else {
        printf("Already at the first song!\n");
    }
}

// 5. Display entire playlist
void displayPlaylist() {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }
    printf("\n--- YOUR PLAYLIST ---\n");
    Song* temp = head;
    int index = 1;
    while (temp != NULL) {
        if (temp == current) {
            printf("%d. [NOW PLAYING] %s - %s\n", index++, temp->title, temp->artist);
        } else {
            printf("%d. %s - %s\n", index++, temp->title, temp->artist);
        }
        temp = temp->next;
    }
    printf("---------------------\n");
}

int main() {
    int choice;
    char title[100], artist[100];

    while (1) {
        printf("\n=== MUSIC PLAYLIST MANAGER ===\n");
        printf("1. Add Song\n");
        printf("2. Delete Song\n");
        printf("3. Play Next Song\n");
        printf("4. Play Previous Song\n");
        printf("5. Show Playlist\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // newline clear karne ke liye

        switch (choice) {
            case 1:
                printf("Enter Song Title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0; // remove trailing newline

                printf("Enter Artist Name: ");
                fgets(artist, sizeof(artist), stdin);
                artist[strcspn(artist, "\n")] = 0;

                addSong(title, artist);
                break;
            case 2:
                printf("Enter Song Title to Delete: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                deleteSong(title);
                break;
            case 3:
                playNext();
                break;
            case 4:
                playPrev();
                break;
            case 5:
                displayPlaylist();
                break;
            case 6:
                printf("Exiting... Have a good day!\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}