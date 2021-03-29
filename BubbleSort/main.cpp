#include<iostream>
#include<algorithm> // std::shuffle
#include<array> // std::array
#include<random> // std::default_random_engine
#include<chrono> // std::chrono
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

// Declaring the list of rectangles, and their corresponding number values
std::array<int, 400> numbers;
sf::RectangleShape rectangles[400];

// Initialises the numbers array
void initNumbers() {
	// Adding the numbers 1 - 400 to the array
	for (int i = 1; i < 400; i++) {
		numbers[i] = i;
	}

	// Seed for default_random_engine function
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	// Shuffling the numbers so that the algorithm can sort them
	std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));
}

// Initialises the Rectangles array
void initRectangles() {
	for (int i = 0; i < 400 - 1; i++) {
		float y = 400 - numbers[i];
		float x = i;
		float height = numbers[i];
		rectangles[i].setPosition(x, y);
		rectangles[i].setSize(sf::Vector2f(1.f, height));
		rectangles[i].setFillColor(sf::Color::White);
	}
} 

// Function that swaps two variables
void swap(int* item1, int* item2) {
	int temp = *item1;
	*item1 = *item2;
	*item2 = temp;
}

int main() {

	// Creates a window with the size (400, 400)
	sf::RenderWindow window(sf::VideoMode(400, 400), "Bubble Sort", sf::Style::Titlebar | sf::Style::Close);

	// A variable to hold the window events
	sf::Event ev;

	// Calls the functions to initialize the numbers and rectangles arrays
	initNumbers();
	initRectangles();

	// Game Loop
	while (window.isOpen()) {
		
		// Event Polling
		while (window.pollEvent(ev)) {
			switch(ev.type) {
			
			// Close the window if the 'x' button is clicked
			case sf::Event::Closed():
				window.close();
				break;
			}
		}

		// Updates
		// The bubble sort algorithm
		// Loops through each of the numbers
		for (int i = 0; i < 400 - 1; i++) {
			
			// If the next number is bigger than the current one, then swap them
			if (numbers[i] > numbers[i + 1]) {
				swap(&numbers[i], &numbers[i + 1]);
				
			}
			// Update the rectangles to represent the current state of the numbers list as it is being sorted
			for (int j = 0; j < 400 - 1; j++) {
				float y = 400 - numbers[j];
				float x = j;
				float height = numbers[j];
				rectangles[j].setPosition(x, y);
				rectangles[j].setSize(sf::Vector2f(1.f, height));
				rectangles[j].setFillColor(sf::Color::White);
			}
			
		}
		
		// Clear the window so that it is reset for the next loop
		window.clear(sf::Color::Black);

		// Render
		// Renders the rectangles so that we can see them in the window
		for (int i = 0; i < 399; i++) {
			window.draw(rectangles[i]);
		}
		
		window.display();
	}

	return 0;
}