#include <stdio.h>

// Function to check if a page is in the frame
int is_page_in_frame(int page, int frame[], int frame_size) {
    for (int i = 0; i < frame_size; i++) {
        if (frame[i] == page) {
            return 1; // Page is found in the frame (hit)
        }
    }
    return 0; // Page is not in the frame (miss)
}

// Function to print the frame state with 'h' for hit and 'm' for miss
void print_frame(int frame[], int frame_size, char hit_or_miss) {
    for (int i = 0; i < frame_size; i++) {
        if (frame[i] == -1) {
            printf("  "); // Replace -1 with two spaces for alignment
        } else {
            printf("%d ", frame[i]);
        }
    }
    printf("| %c\n", hit_or_miss);
}

// Function to implement the FIFO page replacement algorithm
int fifo_page_replacement(int pages, int pageArray[], int frame_size) {
    int frame[frame_size];
    int pageFaults = 0;
    int frameIndex = 0;

    for (int i = 0; i < frame_size; i++) {
        frame[i] = -1; // Initialize the frame with -1 indicating empty frames
    }

    for (int i = 0; i < pages; i++) {
        if (!is_page_in_frame(pageArray[i], frame, frame_size)) {
            pageFaults++;
            frame[frameIndex] = pageArray[i];
            print_frame(frame, frame_size, 'm');
            frameIndex = (frameIndex + 1) % frame_size;
        } else {
            print_frame(frame, frame_size, 'h');
        }
    }
    return pageFaults;
}

//find the least used page
int get_least_recently_used_index(int pageArray[], int frame[], int frame_size, int current_index) {
    int least_recent = current_index;
    int index = -1;

    for (int i = 0; i < frame_size; i++) {
        for (int j = current_index - 1; j >= 0; j--) {
            if (frame[i] == pageArray[j]) {
                if (j < least_recent) {
                    least_recent = j;
                    index = i;
                }
                break;
            }
        }
    }

    return index;
}


// Function to implement the LRU page replacement algorithm
int lru_page_replacement(int pages, int pageArray[], int frame_size) {
    int frame[frame_size];
    int pageFaults = 0;

    for (int i = 0; i < frame_size; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < pages; i++) {
        if (!is_page_in_frame(pageArray[i], frame, frame_size)) {
            pageFaults++;

            if (pageFaults <= frame_size) {
                // If there are available frames, fill them first
                for (int j = 0; j < frame_size; j++) {
                    if (frame[j] == -1) {
                        frame[j] = pageArray[i];
                        break;
                    }
                }
            } else {
                // If all frames are filled, find the least recently used page and replace it
                int replace_index = get_least_recently_used_index(pageArray, frame, frame_size, i);
                frame[replace_index] = pageArray[i];
            }
            print_frame(frame, frame_size, 'm');
        } else {
            print_frame(frame, frame_size, 'h');
        }
    }
    return pageFaults;
}

// Function to find the farthest page in the future
int get_farthest_page_in_future(int pageArray[], int frame[], int frame_size, int current_index, int pages) {
    int farthest = -1;
    int index = -1;

    for (int i = 0; i < frame_size; i++) {
        int found = 0;
        for (int j = current_index + 1; j < pages; j++) {
            if (frame[i] == pageArray[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                found = 1;
                break;
            }
        }
        if (found == 0) {
            // If a page will not be referenced in the future, it is the farthest
            return i;
        }
    }
    return index;
}

// Function to implement the Optimal page replacement algorithm
int optimal_page_replacement(int pages, int pageArray[], int frame_size) {
    int frame[frame_size];
    int pageFaults = 0;

    for (int i = 0; i < frame_size; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < pages; i++) {
        if (!is_page_in_frame(pageArray[i], frame, frame_size)) {
            pageFaults++;

            if (pageFaults <= frame_size) {
                // If there are available frames, fill them first
                for (int j = 0; j < frame_size; j++) {
                    if (frame[j] == -1) {
                        frame[j] = pageArray[i];
                        break;
                    }
                }
            } else {
                // If all frames are filled, find the farthest page in the future and replace it
                int replace_index = get_farthest_page_in_future(pageArray, frame, frame_size, i, pages);
                frame[replace_index] = pageArray[i];
            }
            print_frame(frame, frame_size, 'm');
        } else {
            print_frame(frame, frame_size, 'h');
        }
    }
    return pageFaults;
}

int main() {
    int pages; // Number of pages
    int frame_size; // Frame size
    int algorithm_choice;
    int pageFaults;

    printf("Enter the number of pages: ");
    scanf("%d", &pages);

    int pageArray[pages]; // Array to store the page reference string
    printf("Enter the page reference string: ");
    for (int i = 0; i < pages; i++) {
        scanf("%d", &pageArray[i]);
    }

    printf("Enter the frame size: ");
    scanf("%d", &frame_size);

    while (1) {

        printf("Choose a page replacement algorithm:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        scanf("%d", &algorithm_choice);

        if (algorithm_choice == 4) {
            break;
        }

        switch (algorithm_choice) {
            case 1:
                pageFaults = fifo_page_replacement(pages, pageArray, frame_size);
                break;
            case 2:
                pageFaults = lru_page_replacement(pages, pageArray, frame_size);
                break;
            case 3:
                pageFaults = optimal_page_replacement(pages, pageArray, frame_size);
                break;
            default:
                printf("Invalid choice\n");
                continue;
        }
        printf("Total Page Faults: %d\n", pageFaults);
    }

    return 0;
}
