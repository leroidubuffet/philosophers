# Philo

This project is an adaptation of the classic programming problem philosophers.

## Project Structure

The project has the following files:

- `bin/`: This directory is used to store the compiled binary files.

- `inc/philo.h`: This header file contains the declarations of functions and structures used in the project.

- `src/main.c`: This file contains the main function, which is the entry point of the program.

- `src/arg_utils.c`: This file contains utility functions related to parsing command-line arguments.

- `src/num_utils.c`: This file contains utility functions related to number manipulation.

- `src/init_program.c`: This file contains functions for initializing the program and its components.

- `src/cleanup.c`: This file contains functions for cleaning up resources and freeing memory.

- `src/init_philos.c`: This file contains functions for initializing the philosophers and their resources.

- `src/time_utils.c`: This file contains utility functions related to time manipulation.

- `Makefile`: This file is used to compile the project. It contains rules for compiling the source files, linking the object files, and cleaning up the project.

## Building the Project

To build the project, navigate to the root directory and run the following command:

```
make
```

This will compile the source files and generate the executable file in the `bin/` directory.

## Running the Program

To run the program, execute the following command:

```
./bin/philo
```

Make sure to provide any necessary command-line arguments as specified in the project requirements.

## Cleaning Up

To clean up the project and remove the compiled binary files, run the following command:

```
make clean
```

This will remove the `bin/` directory and its contents.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.
