#include "Shader.h"

Shader::Shader() :
	vertexID(0),
	fragmentID(0),
	programID(0),
	vertexSource(),
	fragmentSource(),
	loaded(false)
{
}

Shader::Shader(Shader const& shaderACopier)
{
	// Copie des fichiers sources
	vertexSource = shaderACopier.vertexSource;
	fragmentSource = shaderACopier.fragmentSource;

	// Chargement du nouveau shader
	load();
}

Shader::Shader(std::string vertexPath, std::string fragmentPath) :
	vertexID(0),
	fragmentID(0),
	programID(0),
	vertexSource(vertexPath),
	fragmentSource(fragmentPath),
	loaded(false)
{
}

Shader::~Shader()
{
	// Destruction du shader
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	glDeleteProgram(programID);
}

Shader& Shader::operator=(Shader const& shaderACopier)
{
	// Copie des fichiers sources
	vertexSource = shaderACopier.vertexSource;
	fragmentSource = shaderACopier.fragmentSource;

	// Chargement du nouveau shader
	load();

	// Retour du pointeur this
	return *this;
}

bool Shader::load()
{
	// Destruction d'un éventuel ancien Shader
	if (glIsShader(vertexID) == GL_TRUE)
		glDeleteShader(vertexID);

	if (glIsShader(fragmentID) == GL_TRUE)
		glDeleteShader(fragmentID);

	if (glIsProgram(programID) == GL_TRUE)
		glDeleteProgram(programID);

	// Compilation des shaders
	if (!compileShader(vertexID, GL_VERTEX_SHADER, vertexSource))
		return false;

	if (!compileShader(fragmentID, GL_FRAGMENT_SHADER, fragmentSource))
		return false;

	// Création du programme
	programID = glCreateProgram();

	// Association des shaders
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);

	// Verrouillage des entrées shader
	glBindAttribLocation(programID, 0, "in_Vertex");
	glBindAttribLocation(programID, 1, "in_Color");
	glBindAttribLocation(programID, 2, "in_TexCoord0");

	// Linkage du programme
	glLinkProgram(programID);

	// Vérification du linkage
	GLint erreurLink(0);
	glGetProgramiv(programID, GL_LINK_STATUS, &erreurLink);

	// S'il y a eu une erreur
	if (erreurLink != GL_TRUE)
	{
		// Récupération de la taille de l'erreur

		GLint tailleErreur(0);
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &tailleErreur);


		// Allocation de mémoire

		char* erreur = new char[(int)(tailleErreur) + 1];


		// Récupération de l'erreur

		glGetShaderInfoLog(programID, tailleErreur, &tailleErreur, erreur);
		erreur[tailleErreur] = '\0';


		// Affichage de l'erreur

		std::cout << erreur << std::endl;


		// Libération de la mémoire et retour du booléen false

		delete[] erreur;
		glDeleteProgram(programID);

		return false;
	}

	loaded = true;
	return true;
		
}

bool Shader::compileShader(GLuint& shader, GLenum type, std::string const& fichierSource)
{
	// Création du shader
	shader = glCreateShader(type);

	// Vérification du shader
	if (shader == 0)
	{
		std::cout << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
		return false;
	}

	// Flux de lecture
	std::ifstream fichier(fichierSource.c_str());

	// Test d'ouverture
	if (!fichier)
	{
		std::cout << "Erreur le fichier " << fichierSource << " est introuvable" << std::endl;
		glDeleteShader(shader);
		return false;
	}

	// Strings permettant de lire le code source
	std::string ligne;
	std::string codeSource;


	// Lecture
	while (getline(fichier, ligne))
		codeSource += ligne + '\n';

	// Fermeture du fichier
	fichier.close();

	// Récupération de la chaine C du code source
	const GLchar* chaineCodeSource = codeSource.c_str();

	// Envoi du code source au shader
	glShaderSource(shader, 1, &chaineCodeSource, 0);

	// Compilation du shader
	glCompileShader(shader);

	// Vérification de la compilation
	GLint erreurCompilation(0);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);

	// S'il y a eu une erreur
	if (erreurCompilation != GL_TRUE)
	{
		// Récupération de la taille de l'erreur
		GLint tailleErreur(0);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);

		// Allocation de mémoire
		char* erreur = new char[((int)tailleErreur) + 1];

		// Récupération de l'erreur
		glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, erreur);
		erreur[tailleErreur] = '\0';

		// Affichage de l'erreur
		std::cout << erreur << std::endl;

		// Libération de la mémoire et retour du booléen false
		delete[] erreur;
		glDeleteShader(shader);

		return false;
	}

	// Sinon c'est que tout s'est bien passé
	else
		return true;
}

GLuint Shader::getProgramID() const
{
	return programID;
}

bool Shader::isLoaded()
{
	return loaded;
}
