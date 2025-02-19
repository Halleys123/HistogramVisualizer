![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) ![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

# Image Histogram Plot

This program allows you to load an image, display it in a window, and show its histogram in another window. It is designed to run on Windows.

## Requirements

- Windows OS
- `make` utility
- MSVC C++ compiler

## Building the Project

To build the project, follow these steps:

1. Open the Command Prompt.
2. Navigate to the project directory:
   ```sh
   cd /d:/Projects/C++/HistogramVisualizer
   ```
3. Run the `make` command:
   ```sh
   make
   ```

This will compile the source files and generate the executable in bin folder.

## Running the Program

After building the project, you can run the executable:

1. In the Command Prompt, navigate to the project directory if not already there:
   ```sh
   cd /d:/Projects/C++/HistogramVisualizer
   ```
2. Run the executable:
   ```sh
   ./main.exe
   ```

## Usage

1. When the program starts, a window will appear with a text field and a button.
2. Enter the path of the image you want to load in the text field.
3. Click the "Load Image" button.
4. Two new windows will appear: one displaying the image and the other displaying the histogram of the image.

## Sample

![Load Panel](./images/load_panel.png)

| Image                             | Histogram                            |
| --------------------------------- | ------------------------------------ |
| ![Image](./images/file_image.png) | ![Histogram](./images/histogram.png) |
| ![alt text](images/imageTwo.png)  | ![alt text](images/imageTwoHist.png) |

## License

This project is licensed under the MIT License.
