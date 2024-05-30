import java.util.InputMismatchException;
import java.util.ArrayList;
import java.util.Scanner;

class Movie {
    private String title;
    private String director;
    private String genre;

    //Constructor
    public Movie(String title, String director, String genre) {
        this.title = title;
        this.director = director;
        this.genre = genre;
    }

    // Getters
    public String getTitle() { return title; }
    public String getDirector() { return director; }
    public String getGenre() { return genre; }

    // Display movie details
    @Override
    public String toString() {
        return "Title: " + title + ", Director: " + director + ", Genre: " + genre;
    }
}

class Collection {
    private ArrayList<Movie> movies;

    public Collection() {
        movies = new ArrayList<>();
    }

    public void addMovie(Movie movie) {
        movies.add(movie);
        System.out.println("Movie added successfully.");
    }

    public void viewMovies() {
        if (movies.isEmpty()) {
            System.out.println("No movies in collection.");
        } else {
            for (Movie movie : movies) {
                System.out.println(movie);
            }
        }
    }

    public void deleteMovie(String title) {
        Movie movieToRemove = null;
        for (Movie movie : movies) {
            if (movie.getTitle().equals(title)) {
                movieToRemove = movie;
                break;
            }
        }
        if (movieToRemove != null) {
            movies.remove(movieToRemove);
            System.out.println("Movie deleted successfully.");
        } else {
            System.out.println("Movie not found.");
        }
    }

    //Search for movie by title, director, or genre
    public void searchMovie(String query) {
        boolean found = false;
        for (Movie movie : movies) {
            if (movie.getTitle().equalsIgnoreCase(query) || movie.getDirector().equalsIgnoreCase(query) || movie.getGenre().equalsIgnoreCase(query)) {
                System.out.println(movie);
                found = true;
            }
        }
        if (!found) {
            System.out.println("No matching movie found.");
        }
    }
}

public class MovieCollectionSystem {
    public static void main(String[] args) {
        Collection collection = new Collection();
        Scanner scanner = new Scanner(System.in);
        int choice = 0;

        do {
            System.out.println("\nMovie Collection System");
            System.out.println("1. Add Movie");
            System.out.println("2. View Movies");
            System.out.println("3. Delete Movie");
            System.out.println("4. Search Movie");
            System.out.println("5. Exit");
            System.out.print("Enter your choice: ");

            try {
                choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline
            }
            catch (InputMismatchException e) {
                System.out.println("Invalid choice. Please try again.");
                scanner.nextLine(); // Consume newline
                continue;
            }

            switch (choice) {
                case 1:
                    System.out.print("Enter movie title: ");
                    String title = scanner.nextLine();
                    System.out.print("Enter movie director: ");
                    String director = scanner.nextLine();
                    System.out.print("Enter movie genre: ");
                    String genre = scanner.nextLine();
                    Movie movie = new Movie(title, director, genre);
                    collection.addMovie(movie);
                    break;
                case 2:
                    collection.viewMovies();
                    break;
                case 3:
                    System.out.print("Enter movie title to delete: ");
                    title = scanner.nextLine();
                    collection.deleteMovie(title);
                    break;
                case 4:
                    System.out.print("Enter movie title, director, or genre to search: ");
                    String query = scanner.nextLine();
                    collection.searchMovie(query);
                    break;
                case 5:
                    System.out.println("Exiting the system.");
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        } while (choice != 5);

        scanner.close();
    }
}