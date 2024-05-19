#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

struct question
{
    char questionText[200];
    char answers[4][200];
    int answer;
    bool isUsed;
};

const int SPORTS = 0, SCIENCE = 1, MUSICART = 2, TVCINEMA = 3, HISTORY = 4, LITERATURE = 5;                                                 // VALORES en forma de números de CADA UNO de los TÓPICOS
int sportsSuccesses = 0, scienceSuccesses = 0, musicartSuccesses = 0, tvcinemaSuccesses = 0, historySuccesses = 0, literatureSuccesses = 0; // VARIABLES QUE ALMACENAN LOS ACIERTOS DE CADA TÓPICO
int SCORE = 0;
int FAILS = 0;

int questionNumber = 1;                                              // variable para Pregunta nºx
bool topicsCompleted[] = {false, false, false, false, false, false}; // Array que indica los tópicos marcados como completados
bool isPlaying = true;

// Estructuras de datos del tipo de estructura question los cuales almacenan todas las preguntas, posibles respuestas y respuestas correctas, además de bool que impide que se repitan entre ellas
struct question sports[20] = {
    {"¿Quién es el máximo goleador en la historia de la selección brasileña de fútbol?", {"A) Romário", "B) Neymar", "C) Pelé", "D) Ronaldo"}, 3, false},
    {"¿Qué país es el actual campeón olímpico de hockey sobre hierba masculino?", {"A) Australia", "B) Alemania", "C) Países Bajos", "D) Argentina"}, 4, false},
    {"¿Qué país ganó la Copa del Mundo de Fútbol en 2014?", {"A) Brasil", "B) Alemania", "C) Argentina", "D) España"}, 2, false},
    {"¿Quién es conocido como “El Rey del Tenis”?", {"A) Rafael Nadal", "B) Roger Federer", "C) Novak Djokovic", "D) Andy Murray"}, 2, false},
    {"¿Cuál es el récord mundial actual de los 100 metros lisos masculinos?", {"A) 9.58 segundos", "B) 9.69 segundos", "C) 9.72 segundos", "D) 9.84 segundos"}, 1, false},
    {"¿Quién ha ganado más títulos de Grand Slam en tenis femenino?", {"A) Serena Williams", "B) Steffi Graf", "C) Margaret Court", "D) Martina Navratilova"}, 3, false},
    {"¿Qué país es el mayor ganador de la Copa América en fútbol?", {"A) Brasil", "B) Argentina", "C) Uruguay", "D) Chile"}, 3, false},
    {"¿Quién fue el primer jugador en anotar 5 goles en un partido de la UEFA Champions League?", {"A) Lionel Messi", "B) Cristiano Ronaldo", "C) Luiz Adriano", "D) Robert Lewandowski"}, 1, false},
    {"¿Cuántos jugadores hay en el campo por equipo en un partido de rugby?", {"A) 11", "B) 13", "C) 15", "D) 18"}, 3, false},
    {"¿Qué país ha ganado más medallas en total en los Juegos Olímpicos de Invierno?", {"A) Noruega", "B) Estados Unidos", "C) Alemania", "D) Canadá"}, 1, false},
    {"¿Cuál es el deporte más popular en todo el mundo?", {"A) Fútbol", "B) Baloncesto", "C) Tenis", "D) Golf"}, 1, false},
    {"¿Cuántos jugadores hay en un equipo de baloncesto en la cancha al mismo tiempo?", {"A) 5", "B) 6", "C) 7", "D) 8"}, 1, false},
    {"¿Qué país es famoso por su pasión por el rugby?", {"A) Nueva Zelanda", "B) Brasil", "C) Japón", "D) España"}, 1, false},
    {"¿En qué año fue la última vez que los Chicago Cubs ganaron la Serie Mundial de béisbol antes de 2016?", {"A) 1945", "B) 1908", "C) 1984", "D) 1995"}, 2, false},
    {"¿En qué ciudad se celebraron los primeros Juegos Olímpicos de la era moderna en 1896?", {"A) Atenas", "B) París", "C) Londres", "D) Roma"}, 1, false},
    {"¿Cuál es la distancia de un maratón oficial en kilómetros?", {"A) 40 kilómetros", "B) 42.195 kilómetros", "C) 38 kilómetros", "D) 45 kilómetros"}, 2, false},
    {"¿Quién es un ajedrecista?", {"A) Magnus Carlsen", "B) Roger Bannister", "C) Pete Sampras", "D) Kareem Abdul-Jabbar"}, 1, false},
    {"¿Quién ganó la medalla de oro en salto con pértiga femenino en los Juegos Olímpicos de Río 2016?", {"A) Jenn Suhr", "B) Yelena Isinbáyeva", "C) Katerina Stefanidi", "D) Sandi Morris"}, 3, false},
    {"¿Qué deporte tiene alrededor de 605 millones de practicantes en el mundo?", {"A) Natación", "B) Ajedrez", "C) Fútbol", "D) Voleyball"}, 2, false},
    {"¿En qué año se celebró la primera Copa Mundial de Fútbol?", {"A) 1928", "B) 1930", "C) 1932", "D) 1934"}, 2, false}};

struct question science[20] = {
    {"¿Cuál es la unidad básica de la vida?", {"A) Átomo", "B) Célula", "C) Virus", "D) Protoplasma"}, 2, false},
    {"¿Qué planetas del sistema solar son conocidos como planetas interiores o terrestres?", {"A) Júpiter y Saturno", "B) Mercurio, Venus, Tierra y Marte", "C) Urano y Neptuno", "D) Plutón y Eris"}, 2, false},
    {"¿Cuál es el proceso por el cual las plantas producen su propio alimento?", {"A) Fotosíntesis", "B) Respiración", "C) Digestión", "D) Transpiración"}, 1, false},
    {"¿Cuál es el hueso más largo del cuerpo humano?", {"A) Fémur", "B) Tibia", "C) Húmero", "D) Radio"}, 1, false},
    {"¿Cuál es la fórmula química del agua?", {"A) H2O", "B) CO2", "C) NaCl", "D) CH4"}, 1, false},
    {"¿Cuál es el gas más abundante en la atmósfera terrestre?", {"A) Oxígeno", "B) Nitrógeno", "C) Dióxido de carbono", "D) Argón"}, 2, false},
    {"¿Cuál es la capa más externa de la Tierra?", {"A) Núcleo", "B) Manto", "C) Corteza", "D) Núcleo interno"}, 3, false},
    {"¿Qué tipo de energía se encuentra almacenada en los alimentos que consumimos?", {"A) Energía térmica", "B) Energía cinética", "C) Energía potencial", "D) Energía química"}, 4, false},
    {"¿Quién descubrió la gravedad cuando una manzana cayó sobre su cabeza?", {"A) Isaac Newton", "B) Albert Einstein", "C) Galileo Galilei", "D) Nikola Tesla"}, 1, false},
    {"¿Qué instrumento se utiliza para medir la presión atmosférica?", {"A) Termómetro", "B) Barómetro", "C) Cronómetro", "D) Dinamómetro"}, 2, false},
    {"¿Cuál es el proceso por el cual el agua líquida se convierte en vapor de agua?", {"A) Sublimación", "B) Evaporación", "C) Fusión", "D) Condensación"}, 2, false},
    {"¿Qué es un ácido según la teoría de Arrhenius?", {"A) Una sustancia que dona protones (H+)", "B) Una sustancia que acepta electrones", "C) Una sustancia que libera oxígeno", "D) Una sustancia que produce gas hidrógeno (H2)"}, 1, false},
    {"¿Cuál es el proceso por el cual las plantas obtienen oxígeno?", {"A) Fotosíntesis", "B) Respiración", "C) Transpiración", "D) Fermentación"}, 1, false},
    {"¿Qué tipo de energía tiene un objeto en movimiento?", {"A) Energía térmica", "B) Energía cinética", "C) Energía potencial", "D) Energía electromagnética"}, 2, false},
    {"¿Cuál es el proceso mediante el cual los organismos vivos obtienen energía de los alimentos?", {"A) Respiración", "B) Digestión", "C) Excreción", "D) Circulación"}, 1, false},
    {"¿Quién propuso la teoría heliocéntrica que sitúa al Sol en el centro del sistema solar?", {"A) Ptolomeo", "B) Copérnico", "C) Kepler", "D) Galileo"}, 2, false},
    {"¿Cuál es la unidad fundamental de la herencia genética?", {"A) Proteína", "B) ADN", "C) ARN", "D) Carbohidrato"}, 2, false},
    {"¿Qué tipo de energía se obtiene a partir de la energía almacenada en los núcleos de átomos?", {"A) Energía solar", "B) Energía eólica", "C) Energía nuclear", "D) Energía geotérmica"}, 3, false},
    {"¿Cuál es la molécula responsable del transporte de oxígeno en la sangre?", {"A) Hemoglobina", "B) Insulina", "C) Queratina", "D) Melanina"}, 1, false},
    {"¿Cuál es la capa más interna de la piel?", {"A) Epidermis", "B) Dermis", "C) Hipodermis", "D) Mesodermis"}, 3, false}};

struct question musicart[20] = {
    {"¿Quién es conocido como el \"Rey del Pop\"?", {"A) Michael Jordan", "B) Michael Jackson", "C) Madonna", "D) Bad Bunny"}, 2, false},
    {"¿Cuál de los siguientes géneros musicales se originó en Jamaica?", {"A) Salsa", "B) Reggae", "C) Flamenco", "D) Cumbia"}, 2, false},
    {"¿Qué instrumento musical tiene cuerdas y se toca frotándolas con un arco?", {"A) Guitarra", "B) Trompeta", "C) Violín", "D) Batería"}, 3, false},
    {"¿Qué famosa banda británica lanzó el álbum \"Sgt. Pepper's Lonely Hearts Club Band\" en 1967?", {"A) The Rolling Stones", "B) The Beatles", "C) Queen", "D) Pink Floyd"}, 2, false},
    {"¿Cómo se llama la técnica de cantar utilizando solo la voz, sin utilizar instrumentos musicales?", {"A) Beatbox", "B) Falsete", "C) Scat", "D) Aria"}, 1, false},
    {"¿En qué década se popularizó el estilo musical conocido como \"disco\"?", {"A) 1960", "B) 1970", "C) 1980", "D) 1990"}, 2, false},
    {"¿Qué célebre compositor austriaco es conocido por sus sinfonías y óperas como \"La Flauta Mágica\"?", {"A) Johann Sebastian Bach", "B) Wolfgang Amadeus Mozart", "C) Ludwig van Beethoven", "D) Franz Schubert"}, 2, false},
    {"¿Qué año fue lanzado el exitoso álbum \"Thriller\" de Michael Jackson?", {"A) 1982", "B) 1984", "C) 1986", "D) 1988"}, 1, false},
    {"¿En qué país se originó el tango, un género musical y baile característico?", {"A) Brasil", "B) Argentina", "C) México", "D) España"}, 2, false},
    {"¿Quién es la cantante femenina más galardonada en la historia de los premios Grammy?", {"A) Adele", "B) Beyoncé", "C) Celine Dion", "D) Aretha Franklin"}, 4, false},
    {"¿Quién pintó la famosa obra \"La última cena\"?", {"A) Vincent van Gogh", "B) Leonardo da Vinci", "C) Pablo Picasso", "D) Michelangelo"}, 2, false},
    {"¿Cuál de estos estilos artísticos se caracteriza por su uso de líneas curvas y formas orgánicas?", {"A) Renacimiento", "B) Barroco", "C) Art Nouveau", "D) Rococó"}, 3, false},
    {"¿En qué siglo vivió el pintor español Diego Velázquez?", {"A) Siglo XV", "B) Siglo XVI", "C) Siglo XVII", "D) Siglo XVIII"}, 3, false},
    {"¿Quién es considerado el fundador del cubismo?", {"A) Claude Monet", "B) Henri Matisse", "C) Pablo Picasso", "D) Salvador Dalí"}, 3, false},
    {"¿Qué pintor famoso es conocido por sus obras surrealistas como \"La persistencia de la memoria\"?", {"A) René Magritte", "B) Salvador Dalí", "C) Frida Kahlo", "D) Jackson Pollock"}, 2, false},
    {"¿Cuál de las siguientes obras es una escultura de Miguel Ángel?", {"A) La Gioconda", "B) La Piedad", "C) La Noche Estrellada", "D) Los girasoles"}, 2, false},
    {"¿Qué movimiento artístico se caracteriza por el uso de colores vibrantes y técnicas expresivas?", {"A) Impresionismo", "B) Expresionismo", "C) Realismo", "D) Romanticismo"}, 2, false},
    {"¿Cuál es una de las obras más famosas del escultor Auguste Rodin?", {"A) El Beso", "B) La Última Cena", "C) La Persistencia de la Memoria", "D) La Noche Estrellada"}, 1, false},
    {"¿Quién pintó \"Los girasoles\"?", {"A) Claude Monet", "B) Vincent van Gogh", "C) Johannes Vermeer", "D) Edvard Munch"}, 2, false},
    {"¿Qué artista es conocido por sus obras en el estilo del \"Pop Art\"?", {"A) Andy Warhol", "B) Georgia O'Keeffe", "C) Wassily Kandinsky", "D) Leonardo da Vinci"}, 1, false}};

struct question tvcinema[20] = {
    {"¿En qué película de Quentin Tarantino aparece la famosa escena de la danza entre John Travolta y Uma Thurman?", {"A) Pulp Fiction", "B) Reservoir Dogs", "C) Kill Bill: Volumen 1", "D) Jackie Brown"}, 1, false},
    {"¿Cuál es el nombre del personaje interpretado por Keanu Reeves en la trilogía de Matrix?", {"A) Neo", "B) Morpheus", "C) Trinity", "D) Agent Smith"}, 1, false},
    {"¿Qué película ganó el premio a la Mejor Película en los Premios de la Academia (Oscar) en 2020?", {"A) 1917", "B) Parasite", "C) Joker", "D) Once Upon a Time in Hollywood"}, 2, false},
    {"¿Cuál de las siguientes series de televisión está ambientada en el mundo de la mafia italiana en Nueva Jersey?", {"A) The Sopranos", "B) Breaking Bad", "C) Fargo", "D) Sons of Anarchy"}, 1, false},
    {"¿Quién interpretó el papel de Jack Dawson en la película Titanic?", {"A) Leonardo DiCaprio", "B) Tom Hanks", "C) Brad Pitt", "D) Johnny Depp"}, 1, false},
    {"¿Cuál es el nombre del robot que protagoniza la película de ciencia ficción “Blade Runner”?", {"A) HAL 9000", "B) R2-D2", "C) WALL-E", "D) Roy Batty"}, 4, false},
    {"¿En qué película se encuentra la famosa frase “Here’s looking at you, kid”?", {"A) Casablanca", "B) Gone with the Wind", "C) Citizen Kane", "D) The Godfather"}, 1, false},
    {"¿Cuál es el nombre del actor que interpreta a Iron Man en el Universo Cinematográfico de Marvel?", {"A) Chris Hemsworth", "B) Chris Evans", "C) Robert Downey Jr.", "D) Mark Ruffalo"}, 3, false},
    {"¿Qué película de ciencia ficción dirigida por Christopher Nolan trata sobre viajes en el tiempo y la manipulación de la realidad?", {"A) Inception (Origen)", "B) Interstellar", "C) The Prestige", "D) Dunkirk"}, 1, false},
    {"¿Cuál es el nombre del personaje interpretado por Anthony Hopkins en “The Silence of the Lambs”?", {"A) Hannibal Lecter", "B) Norman Bates", "C) Patrick Bateman", "D) Dexter Morgan"}, 1, false},
    {"¿Cuál es el nombre del personaje principal en la serie de televisión “Breaking Bad”?", {"A) Walter White", "B) Jesse Pinkman", "C) Saul Goodman", "D) Hank Schrader"}, 1, false},
    {"¿En qué película de Disney se encuentra el personaje Simba?", {"A) La Bella y la Bestia", "B) Aladdín", "C) El Rey León", "D) Mulán"}, 3, false},
    {"¿Quién interpretó a Katniss Everdeen en la saga de películas “Los juegos del hambre”?", {"A) Emma Watson", "B) Jennifer Lawrence", "C) Kristen Stewart", "D) Shailene Woodley"}, 2, false},
    {"¿Cuál es el nombre del bar en el que se reúnen los personajes principales en la serie “Friends”?", {"A) Central Perk", "B) The Regal Beagle", "C) MacLaren’s Pub", "D) Paddy’s Pub"}, 1, false},
    {"¿Qué película de ciencia ficción dirigida por Ridley Scott presenta a un androide llamado David?", {"A) Blade Runner", "B) Alien", "C) Prometheus", "D) The Martian"}, 3, false},
    {"¿Cuál de las siguientes películas fue dirigida por Quentin Tarantino?", {"A) Fight Club", "B) Kill Bill: Volumen 1", "C) The Departed", "D) No Country for Old Men"}, 2, false},
    {"¿En qué película se encuentra la famosa frase “May the Force be with you”?", {"A) Star Wars: Episode IV - A New Hope", "B) Star Trek: The Wrath of Khan", "C) Guardians of the Galaxy", "D) The Matrix"}, 1, false},
    {"¿Cuál es el nombre del personaje interpretado por Johnny Depp en la saga de películas “Piratas del Caribe”?", {"A) Capitán Barbossa", "B) Will Turner", "C) Davy Jones", "D) Jack Sparrow"}, 4, false},
    {"¿En qué película se encuentra la famosa escena de la ducha con música de violines?", {"A) Psycho", "B) The Shining", "C) The Sixth Sense", "D) The Exorcist"}, 1, false},
    {"¿Cuál es el nombre del personaje interpretado por Hugh Jackman en la saga de películas de X-Men?", {"A) Magneto", "B) Wolverine", "C) Professor X", "D) Cyclops"}, 2, false}};

struct question history[20] = {
    {"¿Quién fue el primer emperador de Roma?", {"A) Augusto", "B) Julio César", "C) Nerón", "D) Trajano"}, 1, false},
    {"¿Qué famoso científico desarrolló la teoría de la relatividad?", {"A) Isaac Newton", "B) Galileo Galilei", "C) Albert Einstein", "D) Marie Curie"}, 3, false},
    {"¿Cuál fue la causa de la Revolución Francesa?", {"A) Escasez de pan", "B) Descontento con la monarquía absoluta", "C) Influencia de la Ilustración", "D) Todas las anteriores"}, 4, false},
    {"¿Quién dirigió la Revolución Rusa en 1917?", {"A) Vladimir Lenin", "B) Joseph Stalin", "C) León Trotsky", "D) Nicolás II"}, 1, false},
    {"¿Qué presidente estadounidense ejerció el mandato más largo?", {"A) Franklin D. Roosevelt", "B) Abraham Lincoln", "C) George Washington", "D) Thomas Jefferson"}, 1, false},
    {"¿En qué período histórico se desarrolló la Edad Antigua?", {"A) Desde la Prehistoria hasta el siglo V d.C.", "B) Desde el siglo V d.C. hasta el siglo XV", "C) Desde el siglo XV hasta el siglo XVIII", "D) Desde el siglo XVIII hasta la actualidad"}, 1, false},
    {"¿Cuál fue la dinastía más famosa de Egipto?", {"A) Dinastía Ptolemaica", "B) Dinastía Ramésida", "C) Dinastía XVIII", "D) Dinastía XXVI"}, 1, false},
    {"¿Qué evento marcó el fin de la Edad Media?", {"A) La caída del Imperio Romano", "B) La Revolución Industrial", "C) La caída de Constantinopla", "D) El descubrimiento de América"}, 3, false},
    {"¿Quién fue el líder de la Reforma Protestante?", {"A) Martín Lutero", "B) Juan Calvino", "C) Enrique VIII", "D) Tomás de Aquino"}, 1, false},
    {"¿Cuál fue la principal causa de la Primera Guerra Mundial?", {"A) Nacionalismo", "B) Imperialismo", "C) Alianzas militares", "D) Asesinato del archiduque Francisco Fernando"}, 4, false},
    {"¿Qué civilización construyó las pirámides de Giza?", {"A) Mesopotamia", "B) China", "C) Egipto", "D) India"}, 3, false},
    {"¿Cuál fue el imperio que conquistó gran parte de Europa, Asia y África en el siglo XIII?", {"A) Imperio Romano", "B) Imperio Persa", "C) Imperio Mongol", "D) Imperio Bizantino"}, 3, false},
    {"¿Quién fue el líder de la Revolución Cubana?", {"A) Fidel Castro", "B) Che Guevara", "C) Fulgencio Batista", "D) Raúl Castro"}, 1, false},
    {"¿Cuál fue la batalla decisiva en la Guerra de las Malvinas?", {"A) Batalla de San Carlos", "B) Batalla de Goose Green", "C) Batalla de Puerto Argentino", "D) Batalla de Tumbledown"}, 3, false},
    {"¿Qué evento marcó el inicio de la Segunda Guerra Mundial?", {"A) Invasión de Polonia por Alemania", "B) Ataque a Pearl Harbor", "C) Batalla de Stalingrado", "D) Bombardeo de Hiroshima"}, 1, false},
    {"¿Cuál fue el imperio más grande de la historia?", {"A) Imperio Romano", "B) Imperio Persa", "C) Imperio Mongol", "D) Imperio Británico"}, 3, false},
    {"¿Quién fue el primer presidente de Estados Unidos?", {"A) George Washington", "B) Thomas Jefferson", "C) John Adams", "D) Benjamin Franklin"}, 1, false},
    {"¿Cuál fue el nombre original de la Gran Muralla China?", {"A) Muralla de Qin", "B) Muralla de Han", "C) Muralla de Ming", "D) Muralla de Tang"}, 1, false},
    {"¿Quién fue el primer presidente de México?", {"A) Benito Juárez", "B) Porfirio Díaz", "C) Vicente Guerrero", "D) Miguel Hidalgo"}, 1, false},
    {"¿Qué evento marcó el inicio de la Revolución Industrial?", {"A) Invención de la máquina de vapor", "B) Descubrimiento de la electricidad", "C) Creación del telégrafo", "D) Desarrollo de la imprenta"}, 1, false},
};

struct question literature[20] = {
    {"¿Qué premio Nobel de Literatura nació en Buenos Aires y murió en París?", {"A) Gabriel García Márquez", "B) Jorge Luis Borges", "C) Mario Vargas Llosa", "D) Pablo Neruda"}, 2, false},
    {"¿Cuál es la novela más traducida de Camilo José Cela?", {"A) La Colmena", "B) La familia de Pascual Duarte", "C) Viaje a la Alcarria", "D) La Regenta"}, 1, false},
    {"¿Quién es el autor de “Rayuela”?", {"A) Julio Cortázar", "B) Gabriel García Márquez", "C) Mario Vargas Llosa", "D) Pablo Neruda"}, 1, false},
    {"¿Qué novela de Víctor Hugo ha sido llevada al teatro musical con mucho éxito?", {"A) Nuestra Señora de París", "B) Los Miserables", "C) Los trabajadores del mar", "D) El hombre que ríe"}, 2, false},
    {"¿Qué filósofo alemán escribió sobre la teoría del superhombre?", {"A) Friedrich Nietzsche", "B) Karl Marx", "C) Arthur Schopenhauer", "D) Martin Heidegger"}, 1, false},
    {"¿Qué autor noruego escribió la obra “Casa de muñecas”?", {"A) Henrik Ibsen", "B) Knut Hamsun", "C) Bjørnstjerne Bjørnson", "D) Sigrid Undset"}, 1, false},
    {"¿Con qué seudónimo firmó su obra el escritor chileno Neftalí Ricardo Reyes?", {"A) Pablo Neruda", "B) Gabriela Mistral", "C) Vicente Huidobro", "D) Pablo de Rokha"}, 1, false},
    {"¿A quiénes odiaban los Capuletos en la obra de Shakespeare?", {"A) A los Montescos", "B) A los Benvolio", "C) A los Mercucio", "D) A los Tybaldo"}, 1, false},
    {"¿Cuál es la alcahueta más famosa de la literatura española?", {"A) La Celestina", "B) La Dama Boba", "C) La Pícara Justina", "D) La Gitanilla"}, 1, false},
    {"Nombra alguna obra de Haruki Murakami.", {"A) “Tokio Blues”", "B) “Crónica del pájaro que da cuerda al mundo”", "C) “1Q84”", "D) Todas las anteriores"}, 4, false},
    {"¿Podrías nombrar a alguno de los grandes escritores que murieron sin obtener un Premio Nobel de Literatura?", {"A) Jorge Luis Borges", "B) Julio Cortázar", "C) J.R.R. Tolkien", "D) Vladimir Nabokov"}, 1, false},
    {"¿Qué personaje de Mary Shelley fue recreado por el protagonista de la novela?", {"A) Drácula", "B) Frankenstein", "C) El Hombre Invisible", "D) El Monstruo de la Laguna Negra"}, 2, false},
    {"¿Cuál fue la primera novela de Umberto Eco?", {"A) “El nombre de la rosa”", "B) “El péndulo de Foucault”", "C) “La isla del día de antes”", "D) “Baudolino”"}, 1, false},
    {"¿Qué personaje de Shakespeare murió a manos de Malcolm?", {"A) Hamlet", "B) Macbeth", "C) Otelo", "D) Romeo"}, 2, false},
    {"En qué idioma escribió la mayor parte de su obra el escritor irlandés Samuel Beckett.", {"A) Inglés", "B) Francés", "C) Irlandés", "D) Latín"}, 2, false},
    {"¿Qué escritor escocés escribió la obra “La Isla del Tesoro”?", {"A) Robert Burns", "B) Walter Scott", "C) Robert Louis Stevenson", "D) James Barrie"}, 3, false},
    {"“Cuando Gregorio Samsa se despertó una mañana después de un sueño intranquilo, se encontró sobre su cama convertido en un monstruoso insecto”. ¿Qué obra comienza de esta manera?", {"A) “Cien años de soledad”", "B) “La metamorfosis”", "C) “1984”", "D) Ninguna es correcta"}, 2, false},
    {"¿Quién escribió la famosa novela “Cien años de soledad”?", {"A) Gabriel García Márquez", "B) Mario Vargas Llosa", "C) Julio Cortázar", "D) Pablo Neruda"}, 1, false},
    {"¿Cuál es el título de la obra de Miguel de Cervantes que narra las aventuras de un hidalgo llamado Alonso Quixano?", {"A) “Don Quijote de la Mancha”", "B) “La Celestina”", "C) “El Lazarillo de Tormes”", "D) “La vida es sueño”"}, 1, false},
    {"¿Qué autor estadounidense escribió la novela “Matar a un ruiseñor”?", {"A) Mark Twain", "B) Harper Lee", "C) John Steinbeck", "D) F. Scott Fitzgerald"}, 2, false},
};

bool allTopicsCompleted()
{
    for (size_t i = 0; i < 6; i++) // 6 es la cantidad de tópicos para recorrer el array de completados
    {
        if (!topicsCompleted[i])
            return false;
        else
            continue;
    }
    return true;
}

bool allQuestionsCompleted(int topic) // funcion infumable que he escrito para comporobar si todas las preguntas de un tópico han sido usadas para, en ese caso, reutilizarlas (no pienso añadir más preguntas a la base de datos)
{
    switch (topic)
    {
    case 0:
        for (int i = 0; i < 20; i++)
        {
            if (!sports[i].isUsed)
                return false;
            else
                continue;
        }
        break;

    case 1:
        for (int i = 0; i < 20; i++)
        {
            if (!science[i].isUsed)
                return false;
            else
                continue;
        }
        break;

    case 2:
        for (int i = 0; i < 20; i++)
        {
            if (!musicart[i].isUsed)
                return false;
            else
                continue;
        }
        break;

    case 3:
        for (int i = 0; i < 20; i++)
        {
            if (!tvcinema[i].isUsed)
                return false;
            else
                continue;
        }
        break;

    case 4:
        for (int i = 0; i < 20; i++)
        {
            if (!history[i].isUsed)
                return false;
            else
                continue;
        }
        break;

    case 5:
        for (int i = 0; i < 20; i++)
        {
            if (!literature[i].isUsed)
                return false;
            else
                continue;
        }
        break;

    default:
        break;
    }

    return true;
}

int topicsLeft()
{
    int TOPICS_COUNT = 6;

    for (int i = 0; i < 6; i++) // 6 es la cantidad de tópicos para recorrer el array de completados
    {
        if (topicsCompleted[i])
            TOPICS_COUNT -= 1;
    }

    return TOPICS_COUNT;
}

void setTopicsUncompleted()
{
    for (size_t i = 0; i < 6; i++)
    {
        topicsCompleted[i] = false;
    }
}

void questions(int topic) // Función encargada de utilizar las preguntas de las estructuras de datos de manera random
{
    srand(time(NULL));
    struct question currentQuestion;
    int question = rand() % 20; // número que indica el índice de la pregunta en el array de manera random

    if (topic == SPORTS && !topicsCompleted[SPORTS])
    {
        if (allQuestionsCompleted(SPORTS))
        {
            for (int i = 0; i < 20; i++)
            {
                sports[i].isUsed = false;
            }
        }

        while (sports[question].isUsed)
        {
            question = rand() % 20;
        }

        currentQuestion = sports[question];
        sports[question].isUsed = true;
    }
    else if (topic == SCIENCE && !topicsCompleted[SCIENCE])
    {
        if (allQuestionsCompleted(SCIENCE))
        {
            for (int i = 0; i < 20; i++)
            {
                science[i].isUsed = false;
            }
        }
        while (science[question].isUsed)
        {
            question = rand() % 20;
        }

        currentQuestion = science[question];
        science[question].isUsed = true;
    }
    else if (topic == MUSICART && !topicsCompleted[MUSICART])
    {
        if (allQuestionsCompleted(MUSICART))
        {
            for (int i = 0; i < 20; i++)
            {
                musicart[i].isUsed = false;
            }
        }
        while (musicart[question].isUsed)
        {
            question = rand() % 20;
        }

        currentQuestion = musicart[question];
        musicart[question].isUsed = true;
    }
    else if (topic == TVCINEMA && !topicsCompleted[TVCINEMA])
    {
        if (allQuestionsCompleted(TVCINEMA))
        {
            for (int i = 0; i < 20; i++)
            {
                tvcinema[i].isUsed = false;
            }
        }
        while (tvcinema[question].isUsed)
        {
            question = rand() % 20;
        }

        currentQuestion = tvcinema[question];
        tvcinema[question].isUsed = true;
    }
    else if (topic == HISTORY && !topicsCompleted[HISTORY])
    {
        if (allQuestionsCompleted(HISTORY))
        {
            for (int i = 0; i < 20; i++)
            {
                history[i].isUsed = false;
            }
        }
        while (history[question].isUsed)
        {
            question = rand() % 20;
        }

        currentQuestion = history[question];
        history[question].isUsed = true;
    }
    else if (topic == LITERATURE && !topicsCompleted[LITERATURE])
    {
        if (allQuestionsCompleted(LITERATURE))
        {
            for (int i = 0; i < 20; i++)
            {
                literature[i].isUsed = false;
            }
        }
        while (literature[question].isUsed)
        {
            question = rand() % 20;
        }

        currentQuestion = literature[question];
        literature[question].isUsed = true;
    }

    int answer;

    printf("\nPREGUNTA Nº%d\n\n", questionNumber);
    questionNumber += 1;

    printf("%s\n", currentQuestion.questionText);
    printf("%s\n", currentQuestion.answers[0]);
    printf("%s\n", currentQuestion.answers[1]);
    printf("%s\n", currentQuestion.answers[2]);
    printf("%s\n", currentQuestion.answers[3]);

    scanf("%d", &answer);

    // printf("%d\n", answer);
    // printf("%d\n", questions[i].answer);

    if (answer == currentQuestion.answer)
    {
        printf("Correcto!\n+1 punto\n");
        SCORE += 1;
        switch (topic) // Comprueba que variables modificar según el tópico que te haya tocado (Ej: si aciertas una pregunta del tópico deportes, las variables asociadas se modifican)
        {
        case 0:
            sportsSuccesses += 1;
            printf("Aciertos de DEPORTES: %d\n", sportsSuccesses);
            if (sportsSuccesses == 3) // En caso de haber acertado 3 preguntas de ese tópico, no aparecerá más
            {
                printf("Has completado el tópico de DEPORTES\n\n");
                topicsCompleted[0] = true;
                printf("Quedan %d TÓPICOS\n", topicsLeft());
            }
            break;
        case 1:
            scienceSuccesses += 1;
            printf("Aciertos de CIENCIA: %d\n", scienceSuccesses);
            if (scienceSuccesses == 3)
            {
                printf("Has completado el tópico de CIENCIA\n\n");
                topicsCompleted[1] = true;
                printf("Quedan %d TÓPICOS\n", topicsLeft());
            }
            break;
        case 2:
            musicartSuccesses += 1;
            printf("Aciertos de MÚSICA Y ARTE: %d\n", musicartSuccesses);
            if (musicartSuccesses == 3)
            {
                printf("Has completado el tópico de MÚSICA Y ARTE\n\n");
                topicsCompleted[2] = true;
                printf("Quedan %d TÓPICOS\n", topicsLeft());
            }
            break;
        case 3:
            tvcinemaSuccesses += 1;
            printf("Aciertos de TELEVISIÓN Y CINE: %d\n", tvcinemaSuccesses);
            if (tvcinemaSuccesses == 3)
            {
                printf("Has completado el tópico de TELEVISIÓN Y CINE\n\n");
                topicsCompleted[3] = true;
                printf("Quedan %d TÓPICOS\n", topicsLeft());
            }
            break;
        case 4:
            historySuccesses += 1;
            printf("Aciertos de HISTORIA: %d\n", historySuccesses);
            if (historySuccesses == 3)
            {
                printf("Has completado el tópico de HISTORIA\n\n");
                topicsCompleted[4] = true;
                printf("Quedan %d TÓPICOS\n", topicsLeft());
            }
            break;
        case 5:
            literatureSuccesses += 1;
            printf("Aciertos de LITERATURA: %d\n", literatureSuccesses);
            if (literatureSuccesses == 3)
            {
                printf("Has completado el tópico de LITERATURA\n\n");
                topicsCompleted[5] = true;
                printf("Quedan %d TÓPICOS\n", topicsLeft());
            }
            break;

        default:
            break;
        }
    }
    else
    {
        printf("Respuesta INCORRECTA! :( la respuesta era: %d\n", currentQuestion.answer);
        FAILS += 1;
    }
}

void trivial(int topic)
{
    // printf("int topic es igual a: %d\n", topic);
    srand(time(NULL));
    int currentTopic = topic;

    if (allTopicsCompleted())
    {
        printf("\n\nSe han terminado todos los tópicos!\n\n");

        printf("PUNTUACIONES:\n");
        printf("Tu puntuación TOTAL: %d\n", SCORE);
        printf("Tus FALLOS: %d\n\n", FAILS);
        printf("Gracias por jugar\n\n");
        return;
    }

    while (topicsCompleted[topic] || (topic == currentTopic && topicsLeft() >= 2))
    {
        topic = rand() % 6;
    }
    // printf("int topic HA CAMBIADO ha %d\n", topic);

    switch (topic)
    {
    case 0:
        printf("\n\nTe ha tocado el topico DEPORTES\n\n");
        break;

    case 1:
        printf("\n\nTe ha tocado el topico CIENCIA\n\n");
        break;

    case 2:
        printf("\n\nTe ha tocado el topico ARTE\n\n");
        break;

    case 3:
        printf("\n\nTe ha tocado el topico TELEVISIÓN\n\n");
        break;

    case 4:
        printf("\n\nTe ha tocado el topico HISTORIA\n\n");
        break;

    case 5:
        printf("\n\nTe ha tocado el topico LITERATURA\n\n");
        break;
    }

    questions(topic);
    trivial(topic);
}

void play()
{
    srand(time(NULL));
    int topic;

    printf("\nTemáticas del TRIVIAL:");
    printf("\n-Deportes\n-Ciencia\n-Arte\n-Televisión\n-Historia\n-Literatura\n\n");
    printf("Se van a mostrar 10 preguntas del tópico que te toque.... ¡Preparate para empezar!\n");
    printf("CONTESTA A CADA UNA DE LAS PREGUNTAS DEL 1 AL 4\n");
    printf("A) = 1\n B) = 2\n C) = 3\n D) = 4\n\n");

    topic = rand() % 6;

    trivial(topic);

    // hacer una funcion para cada tipo de tópico (o una funcion que, dependiendo los parámetros use un tipo de preguntas u otra)
    // almacenar de 20 de las preguntas de un tópico, 10 de ellas y usarlas de manera random
    // PD: definitivamente me debí de haber ido a FP
}

void menu()
{
    int option;
    printf("\nTRIVIAL\n");
    printf("1 --> Jugar\n2 --> Salir\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        SCORE = 0;
        FAILS = 0;

        questionNumber = 1;
        setTopicsUncompleted();
        sportsSuccesses = 0;
        scienceSuccesses = 0;
        musicartSuccesses = 0;
        tvcinemaSuccesses = 0;
        historySuccesses = 0;
        literatureSuccesses = 0;

        for (int i = 0; i < 20; i++)
        {
            sports[i].isUsed = false;
            science[i].isUsed = false;
            musicart[i].isUsed = false;
            tvcinema[i].isUsed = false;
            history[i].isUsed = false;
            literature[i].isUsed = false;
        }

        play();
        break;

    case 2:
        printf("Saliendo del juego...\n");
        isPlaying = false;

    default:
        return;
    }
}

int main()
{
    while (isPlaying)
        menu();
    return 0;
}