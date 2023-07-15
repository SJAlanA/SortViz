#include <SDL2/SDL.h>
#include <bits/stdc++.h>
using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 750;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool complete = false;

const int arrSize = 150;
const int rectSize = 7;

int arr[arrSize];
int Barr[arrSize];

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Couldn't initialize SDL. SDL_Error: " << SDL_GetError();
        success = false;
    }
    else
    {
        if (!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")))
        {
            cout << "Warning: Linear Texture Filtering not enabled.\n";
        }

        window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            cout << "Couldn't create window. SDL_Error: " << SDL_GetError();
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                cout << "Couldn't create renderer. SDL_Error: " << SDL_GetError();
                success = false;
            }
        }
    }

    return success;
}

void close()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

void start()
{
    cout << "#############################################################\n"
         << endl;
    cout << " _______  _______  ______    _______  __   __  ___   _______ " << endl;
    cout << "|       ||       ||    _ |  |       ||  | |  ||   | |       |" << endl;
    cout << "|  _____||   _   ||   | ||  |_     _||  |_|  ||   | |____   |" << endl;
    cout << "| |_____ |  | |  ||   |_||_   |   |  |       ||   |  ____|  |" << endl;
    cout << "|_____  ||  |_|  ||    __  |  |   |  |       ||   | | ______|" << endl;
    cout << " _____| ||       ||   |  | |  |   |   |     | |   | | |_____ " << endl;
    cout << "|_______||_______||___|  |_|  |___|    |___|  |___| |_______|" << endl;
    cout << "\n                                   Coded by SAHAI JORDI ALAN A" << endl;
    cout << "\n############################################################" << endl;

    cout << "This program is designed to visually demonstrate various sorting algorithms in action. By using C++ programming language and SDL2 library, I have created a sorting visualizer that allows you to see how different sorting algorithms work step by step."
         << "The visualizer provides a real-time animation that displays the sorting process, allowing you to observe how the elements move and swap positions."
         << "As you run the program, you will be able to choose from a range of sorting algorithms, such as Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, Quick Sort, and more. Each algorithm will be visually represented, showing the step-by-step process of rearranging the elements in the input array.";

    string s;
    getline(cin, s);
    if (s == "\n")
        return;
}

bool controls()
{

    cout << "Click the Corresponding numbers to visualise the corresponding functions\n"
         << "   0 : Generate a different randomized list.\n"
         << "   1 : Selection Sort Algorithm.\n"
         << "   2 : Insertion Sort Algorithm.\n"
         << "   3 : Bubble Sort Algorithm.\n"
         << "   4 : Merge Sort Algorithm.\n"
         << "   5 : Quick Sort Algorithm.\n"
         << "   6 : Heap Sort Algorithm.\n"
         << "   q : to exit out of Sorting Visualiser\n\n"
         << "PRESS ENTER TO SEE THE SORTING VISUALISER OR ENTER -1 TO QUIT ! \n";

    string s;
    getline(cin, s);
    if (s == "-1")
        return false;
    return true;
}

void visualize(int x = -1, int y = -1, int z = -1)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    int j = 0;
    for (int i = 0; i <= SCREEN_WIDTH - rectSize; i += rectSize)
    {
        SDL_PumpEvents();

        SDL_Rect rect = {i, 0, rectSize, arr[j]};
        if (complete)
        {
            SDL_SetRenderDrawColor(renderer, 100, 180, 100, 0);
            SDL_RenderDrawRect(renderer, &rect);
        }
        else if (j == x || j == z)
        {
            SDL_SetRenderDrawColor(renderer, 100, 180, 100, 0);
            SDL_RenderFillRect(renderer, &rect);
        }
        else if (j == y)
        {
            SDL_SetRenderDrawColor(renderer, 165, 105, 189, 0);
            SDL_RenderFillRect(renderer, &rect);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 170, 183, 184, 0);
            SDL_RenderDrawRect(renderer, &rect);
        }
        j++;
    }
    SDL_RenderPresent(renderer);
}

void loadArr()
{
    // The memory is copied from Barr to arr
    memcpy(arr, Barr, sizeof(int) * arrSize);
}

void randomizeAndSaveArray()
{
    // Create a random array based on the current time
    unsigned int seed = (unsigned)time(NULL);
    srand(seed);

    // Store the values in the array
    for (int i = 0; i < arrSize; i++)
    {
        // To fit the screen
        int random = rand() % (SCREEN_HEIGHT);
        Barr[i] = random;
    }
}

void inplaceHeapSort(int *input, int n)
{
    for (int i = 1; i < n; i++)
    {
        int childIndex = i;
        int parentIndex = (childIndex - 1) / 2;

        while (childIndex > 0)
        {
            if (input[childIndex] > input[parentIndex])
            {
                int temp = input[parentIndex];
                input[parentIndex] = input[childIndex];
                input[childIndex] = temp;
            }
            else
            {
                break;
            }

            visualize(parentIndex, childIndex);
            SDL_Delay(40);

            childIndex = parentIndex;
            parentIndex = (childIndex - 1) / 2;
        }
    }

    for (int heapLast = n - 1; heapLast >= 0; heapLast--)
    {
        int temp = input[0];
        input[0] = input[heapLast];
        input[heapLast] = temp;

        int parentIndex = 0;
        int leftChildIndex = 2 * parentIndex + 1;
        int rightChildIndex = 2 * parentIndex + 2;

        while (leftChildIndex < heapLast)
        {
            int maxIndex = parentIndex;

            if (input[leftChildIndex] > input[maxIndex])
            {
                maxIndex = leftChildIndex;
            }
            if (rightChildIndex < heapLast && input[rightChildIndex] > input[maxIndex])
            {
                maxIndex = rightChildIndex;
            }
            if (maxIndex == parentIndex)
            {
                break;
            }

            int temp = input[parentIndex];
            input[parentIndex] = input[maxIndex];
            input[maxIndex] = temp;

            visualize(maxIndex, parentIndex, heapLast);
            SDL_Delay(40);

            parentIndex = maxIndex;
            leftChildIndex = 2 * parentIndex + 1;
            rightChildIndex = 2 * parentIndex + 2;
        }
    }
}

void swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

int partition_array(int a[], int l, int h)
{
    int count_small = 0;

    for (int i = (l + 1); i <= h; i++)
    {
        if (a[i] <= a[l])
        {
            count_small++;
        }
    }
    int pivot = l + count_small;
    swap(&a[pivot], &a[l]);
    visualize(pivot, l);

    int i = l, j = h;

    while (i < pivot && j > pivot)
    {
        if (a[i] <= a[pivot])
        {
            i++;
        }
        else if (a[j] > a[pivot])
        {
            j--;
        }
        else
        {
            swap(&a[i], &a[j]);

            visualize(i, j);
            SDL_Delay(70);

            i++;
            j--;
        }
    }
    return pivot;
}

void quickSort(int a[], int l, int h)
{
    if (l >= h)
    {
        return;
    }

    int pivot = partition_array(a, l, h);
    quickSort(a, l, pivot - 1);
    quickSort(a, pivot + 1, h);
}

void mergethem(int a[], int l, int h)
{
    int size_output = (h - l) + 1;
    int *output = new int[size_output];

    int mid = (l + h) / 2;
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= h)
    {
        if (a[i] <= a[j])
        {
            output[k] = a[i];
            visualize(i, j);
            i++;
            k++;
        }
        else
        {
            output[k] = a[j];
            visualize(i, j);
            j++;
            k++;
        }
    }
    while (i <= mid)
    {
        output[k] = a[i];
        visualize(-1, i);
        i++;
        k++;
    }
    while (j <= h)
    {
        output[k] = a[j];
        visualize(-1, j);
        j++;
        k++;
    }
    int x = 0;
    for (int k = l; k <= h; k++)
    {
        a[k] = output[x];
        visualize(k);
        SDL_Delay(15);
        x++;
    }
    delete[] output;
}

void mergeSort(int a[], int l, int h)
{
    if (l >= h)
    {
        return;
    }
    int mid = (l + h) / 2;

    mergeSort(a, l, mid);
    mergeSort(a, mid + 1, h);

    mergethem(a, l, h);
}

void bubbleSort()
{
    for (int i = 0; i < arrSize - 1; i++)
    {
        for (int j = 0; j < arrSize - 1 - i; j++)
        {
            if (arr[j + 1] < arr[j])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                visualize(j + 1, j, arrSize - i);
            }
            SDL_Delay(1);
        }
    }
}

void insertionSort()
{
    for (int i = 1; i < arrSize; i++)
    {
        int j = i - 1;
        int temp = arr[i];
        while (j >= 0 && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            j--;

            visualize(i, j + 1);
            SDL_Delay(5);
        }
        arr[j + 1] = temp;
    }
}

void selectionSort()
{
    int minIndex;
    for (int i = 0; i < arrSize - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < arrSize; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
                visualize(i, minIndex);
            }
            SDL_Delay(1);
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

void execute()
{
    // Check if SDL initiated or not
    if (!init())
    {
        cout << "SDL Initialization Failed.\n";
    }
    else
    {
        // Create a randomized array of values
        randomizeAndSaveArray();
        loadArr();

        SDL_Event e;
        bool quit = false;
        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                    complete = false;
                }
                else if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                    case (SDLK_q):
                        quit = true;
                        complete = false;
                        cout << "\nEXIT!\n";
                        break;
                    case (SDLK_0):
                        randomizeAndSaveArray();
                        complete = false;
                        loadArr();
                        cout << "\nARRAY VALUES ARE RANDOMIZED!\n";
                        break;
                    case (SDLK_1):
                        // Loading the current array
                        loadArr();
                        cout << "\nINITIATED SELECTION SORT!\n";
                        complete = false;
                        // Selection sort started
                        selectionSort();
                        // Selection sort is finished
                        complete = true;
                        cout << "\nSELECTION SORT FINISHED!\n";
                        break;
                    case (SDLK_2):
                        loadArr();
                        cout << "\nnINITIATED INSERTION SORT!\n";
                        complete = false;
                        insertionSort();
                        complete = true;
                        cout << "\nINSERTION SORT FINISHED!\n";
                        break;
                    case (SDLK_3):
                        loadArr();
                        cout << "\nINITIATED BUBBLE SORT!\n";
                        complete = false;
                        bubbleSort();
                        complete = true;
                        cout << "\nBUBBLE SORT FINISHED!\n";
                        break;
                    case (SDLK_4):
                        loadArr();
                        cout << "\nINITIATED MERGE SORT!\n";
                        complete = false;
                        mergeSort(arr, 0, arrSize - 1);
                        complete = true;
                        cout << "\nMERGE SORT FINISHED!\n";
                        break;
                    case (SDLK_5):
                        loadArr();
                        cout << "\nINITIATED QUICK SORT!\n";
                        complete = false;
                        quickSort(arr, 0, arrSize - 1);
                        complete = true;
                        cout << "\nQUICK SORT FINISHED!\n";
                        break;
                    case (SDLK_6):
                        loadArr();
                        cout << "\nINITIATED HEAP SORT!\n";
                        complete = false;
                        inplaceHeapSort(arr, arrSize);
                        complete = true;
                        cout << "\nHEAP SORT FINISHED!\n";
                        break;
                    }
                }
            }
            visualize();
        }
        close();
    }
}

int main(int argv, char *args[])
{
    start();

    while (1)
    {
        cout << '\n';
        if (controls())
            execute();
        else
        {
            cout << "\nEXIT!\n";
            break;
        }
    }

    return 0;
}