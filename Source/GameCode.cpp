#include "gamecode.h"
#include "windef.h"
#include "gamescript.h"
#include "CString"
#include <cstdlib>
#include <stdio.h>
#include <string>

using namespace std;

LPD3DXSPRITE SpHd;												//Sprite Handler

LPDIRECT3DTEXTURE9 menu_box;									//Menu Textures
LPDIRECT3DTEXTURE9 menu_header;
LPDIRECT3DTEXTURE9 menu_word_view;
LPDIRECT3DTEXTURE9 menu_speed_change;
LPDIRECT3DTEXTURE9 menu_mute_sounds;
LPDIRECT3DTEXTURE9 menu_exit_menu;
LPDIRECT3DTEXTURE9 menu_exit_game;
LPDIRECT3DTEXTURE9 menu_fader;

LPDIRECT3DTEXTURE9 introduction;								//Introduction Screen Texture
LPDIRECT3DTEXTURE9 title;										//Title Screen Texture
LPDIRECT3DTEXTURE9 arrow;										//Arrow Texture for Word Processing
LPDIRECT3DTEXTURE9 forest;										//Forest Texture
LPDIRECT3DTEXTURE9 HUD_out;										//Outer Interface Texture
LPDIRECT3DTEXTURE9 HUD_in;										//Inner Interface Texture

LPDIRECT3DTEXTURE9 anime;
LPDIRECT3DTEXTURE9 ct;
LPDIRECT3DTEXTURE9 eend;
LPDIRECT3DTEXTURE9 triton;
LPDIRECT3DTEXTURE9 hamburger;
LPDIRECT3DTEXTURE9 koala1;
LPDIRECT3DTEXTURE9 koala2;
LPDIRECT3DTEXTURE9 apoc;
LPDIRECT3DTEXTURE9 ufo;
LPDIRECT3DTEXTURE9 balloons;
LPDIRECT3DTEXTURE9 boat;
LPDIRECT3DTEXTURE9 eyes;
LPDIRECT3DTEXTURE9 heart;
LPDIRECT3DTEXTURE9 hotel;
LPDIRECT3DTEXTURE9 housein;
LPDIRECT3DTEXTURE9 loading;
LPDIRECT3DTEXTURE9 mansion;
LPDIRECT3DTEXTURE9 map;
LPDIRECT3DTEXTURE9 medal;
LPDIRECT3DTEXTURE9 party;
LPDIRECT3DTEXTURE9 rest1;
LPDIRECT3DTEXTURE9 rest2;
LPDIRECT3DTEXTURE9 sunny;
LPDIRECT3DTEXTURE9 rainy;
LPDIRECT3DTEXTURE9 tombstone;
LPDIRECT3DTEXTURE9 yale;

LPDIRECT3DTEXTURE9 view_arrow1;
LPDIRECT3DTEXTURE9 view_arrow2;
LPDIRECT3DTEXTURE9 view_bg;
LPDIRECT3DTEXTURE9 view_slider;
LPDIRECT3DTEXTURE9 view_blockers;

LPDIRECT3DSURFACE9 back;										//Secondary Surface

LPD3DXFONT help_font = NULL;									//Font Holders
LPD3DXFONT title_font = NULL;
LPD3DXFONT speed_font = NULL;
LPD3DXFONT speed_select_font = NULL;
LPD3DXFONT name_font = NULL;
LPD3DXFONT name_select_font = NULL;
LPD3DXFONT game_font = NULL;
LPD3DXFONT view_font = NULL;

D3DCOLOR White = D3DCOLOR_XRGB(255, 255, 255);

char* String_Convert(string str);								//Convert string to char*
string String_Combine(char* string1, char* string2);			//Convert char* to string and combine

void Game();													//Primary Loop

void Introduction();											//Independent Introduction Screen
void Title_Screen();											//Independent Title Screen
void Speed_Select();											//Independent Speed Selection Screen
void Speed_Select_Sub(int alpha1,								//Subsidiary Speed Picking Function
					  int alpha2,
					  int alpha3, 
					  int alpha4, 
					  int alpha5);

void Name_Select();												//Independent Name Selection Screen

int Menu(HWND hwnd);											//Secondary Menu Engine

void Menu_Sub(int alpha1,										//Menu Engine Subsidiary
			 int alpha2,
			 int alpha3,
			 int alpha4,
			 int alpha5,
			 int alpha6,
			 int alpha7);

void Fade_Out();

int Wait(int time);

void Activate();

void Speed_Change();											//Speed Change Function for the Menu

void View_Words();												//View Words Function for the Menu

void Load_Words(char* str1,										//Subsidiary Function for Loading Past Words
			   char* str2,
			   char* str3,
			   char* str4,
			   char* str5,
			   char* str6,
			   char* str7,
			   char* str8,
			   char* str9,
			   char* str10,
			   char* str11);

void Visual_Novel();											//Primary Game Engine User

int HUD_Display(int x);											//Subsidiary Interface Appearing Function
int HUD_Vanish(int x);											//Subsidiary Interface Vanish Function
void HUD_Reset();

int Word_Processor(char* words,									//Subsidiary Word Processing Function
				   char* name,
					int speed,									//Returns 1 when complete, 0 when incomplete
					int r,
					int g,
					int b,
					int choices);

class Background												//Background Class
{
	private:
		int x;
		int y;
		int alpha;
		int ainc;
		int adec;
		int delay;
		int load;												//One Thing Thing
		D3DXVECTOR3 position;									//Position Vector
		D3DCOLOR color;											//Tint just in case
		LPDIRECT3DTEXTURE9 texture;								//Texture

	public:
		Background(int X, int Y);								//Constructor Function

		~Background(){};										//Destructor Function

		void Change_Texture(LPDIRECT3DTEXTURE9 Texture);		//Change Texture Function

		void Reload();											//Allows for Another Change

		void Reset();

		int Display(int Ainc,									//Subsidiary Appearing Function
			int Delay);											//Returns 1 if complete, 0 if incomplete

		int Vanish(int Adec,									//Subsidiary Vanish Function
			int Delay);											//Returns 1 if complete, 0 if incomplete

		int Effect();											//Experimental Effect Function
};

class Character													//Character Class
{
	private:
		int x;
		int y;
		int alpha1;
		int alpha2;
		int ainc;
		int adec;
		int delay;
		int load;
		int repose;
		int vanish_status;
		int movex;												//Movement Variables
		int movex_tick;
		int movey;
		int movey_tick;
		int move_time;
		D3DXVECTOR3 position1;									//Position Vector
		D3DXVECTOR3 position2;									//Secondary Position Used For Vanish
		D3DCOLOR color;	
		LPDIRECT3DTEXTURE9 texture1;
		LPDIRECT3DTEXTURE9 texture2;
		LPDIRECT3DTEXTURE9 texture3;
		LPDIRECT3DTEXTURE9 texture4;
		LPDIRECT3DTEXTURE9 texture5;
		LPDIRECT3DTEXTURE9 texture6;
		LPDIRECT3DTEXTURE9 texture7;
		LPDIRECT3DTEXTURE9 texture8;
		LPDIRECT3DTEXTURE9 texture9;

	public:
		Character(int X, int Y);								//Constructor Function

		~Character(){};											//Destructor Function

		void Change_Texture(LPDIRECT3DTEXTURE9 Texture,			//Change Texture Function
			int Number);

		void Reload();											//Allow Change in Alpha Variables

		void Prepare();											//Allow Change in X and Y

		void Relocate(int X, int Y);							//Changes X and Y

		void Reset();

		int Display(int Ainc,									//Subsidiary Appearing Function
			int Delay,
			int Number);										//Returns 1 if complete, 0 if incomplete

		int Vanish(int Adec,									//Subsidiary Vanish Function
			int Delay,
			int Number);										//Returns 1 if complete, 0 if incomplete

		int Move(int Movex,
			int Movey,
			int Move_time);

		int Effect();											//Experimental Effect Function
};

long int intro_count = 0;										//Counter
int intro_status = 1;											//Lock
int intro_alpha = -150;											//Alpha
int intro_ainc = 5;												//Alpha Increase
int intro_adec = 0;												//Alpha Decrease

long int title_count = 0;
int title_status = 0;
int title_alpha = 0;
int title_button_status = 0;									//Button Lock
int title_ainc = 0;
int title_adec = 0;
int title_letters_active = 1;									//Disable
int title_letters_ainc = 1;
int title_letters_adec = 0;
int title_letters_alpha = 0;
char* title_string = "Press Enter to Begin";

int help_alpha = 0;
int help_ainc = 0;
int help_adec = 0;
long int help_counter = 0;
char* help_string = "That strawberry was the sweetest one I've ever eaten!";

int speed_status = 0;
long int speed_count = 0;
long int speed_count_keeper = 0;								//Speed Variator for Selection Process
int speed_button_status = 5;
int speed_alpha = 0;
int speed_ainc = 3;
int speed_adec = 0;
int speed_main_alpha = 0;										//Main means currently selected
int speed_others_alpha = 0;
int speed_main_ainc = 5;
int speed_main_adec = 3;
int speed_others_ainc = 3;										//Others means unselected
int speed_others_adec = 5;
int speed_pick = 3;												//Current Choice
int speed_input = 3;											//Actual Choice
char* speed_string = "Please Select Your Reading Speed";

int name_status = 0;
long int name_count = 0;
int name_alpha = 0;
int name_ainc = 3;
int name_adec = 0;
int name_input_alpha = 255;
int name_input_adec = 0;
int name_button_status = 0;
int name_count_keeper = 0;
char* name_string = "Please Insert Your Name";
char* name_input_string = "";									//Selected Name
string name_string_holder = "";									//Holder for Conversion Purpose

int game_font_alpha = 255;
int game_font_ainc = 0;
int game_font_adec = 0;
int game_font_active = 0;
int game_font_status = 0;

int VN_status = 0;												//Game Engine Controller

int words_active = 1;											//Controls Word Processor During Fading

int HUD_status = 0;
int HUD_done = 0;
int HUD_out_alpha = 0;
int HUD_out_ainc = 3;
int HUD_out_adec = 1;
int HUD_in_alpha = 0;
int HUD_in_ainc = 3;
int HUD_in_adec = 1;
long int HUD_count = 0;

int background_status = 0;
int background_alpha = 0;
int background_ainc = 0;
int background_adec = 0;
long int background_count = 0;

long int word_tick = 1;
long int word_count = 0;
long int word_count_keeper = 0;
int word_arrowx = 360;
int word_arrowy = 244;

int menu_status = 0;
int menu_main_alpha = 255;
int menu_others_alpha = 150;
int menu_main_ainc = 0;
int menu_others_ainc = 0;
int menu_main_adec = 0;
int menu_others_adec = 0;
long int menu_count = 0;
long int menu_count_keeper = 0;
int menu_pick = 1;

int speedc_status = 0;
long int speedc_count = 0;
long int speedc_count_keeper = 0;
int speedc_button_status = 10;
int speedc_alpha = 0;
int speedc_ainc = 3;
int speedc_adec = 0;
int speedc_main_alpha = 0;
int speedc_others_alpha = 0;
int speedc_main_ainc = 5;
int speedc_main_adec = 3;
int speedc_others_ainc = 3;
int speedc_others_adec = 5;
int speedc_pick = 3;
char* speedc_string = "Please repick Your Reading Speed";

int fade_status = 0;
int fade_alpha = 0;
int fade_ainc = 5;
int fade_adec = 5;
long int fade_count = 0;

int fade_vn = 0;												//If Fading Out From Visual Novel
int fade_menu = 0;												//If Fading Out From Menu to Visual Novel
int fade_menu_speedc = 0;										//If Fading Out From Menu to Speed Change
int fade_menu_view = 0;											//If Fading Out From Menu to Word Viewer
int fade_speedc = 0;											//If Fading Out From Speed Change
int fade_word_view = 0;											//If Fading Out From Word Viewer

int wait_count = 0;

int view_status = 0;
int view_active = 0;
int view_y = 0;													//Movement Variables
int view_slider_y = 0;
char* vs1;
char* vs2;
char* vs3;
char* vs4;
char* vs5;
char* vs6;
char* vs7;
char* vs8;
char* vs9;
char* vs10;
char* vs11;

int phase = 0;

int sound_status = 1;

int VN_active = 1;
int menu_active = 0;

Background Anime(0, 0);
Background Ct(0, 0);
Background End(0, 0);
Background Triton(0, 0);
Background Hamburger(0, 0);
Background Koala1(0, 0);
Background Koala2(0, 0);
Background Apoc(0, 0);
Background Ufo(0, 0);
Background Balloons(0, 0);
Background Boat(0, 0);
Background Eyes(0, 0);
Background Heart(0, 0);
Background Hotel(0, 0);
Background Housein(0, 0);
Background Loading(0, 0);
Background Mansion(0, 0);
Background Map(0, 0);
Background Medal(0, 0);
Background Party(0, 0);
Background Rest1(0, 0);
Background Rest2(0, 0);
Background Sunny(0, 0);
Background Rainy(0, 0);
Background Tombstone(0, 0);
Background Yale(0, 0);

Background Forest(0, 0);

Character Snow(0, 20);

HRESULT result;													//Needed for Loading Sprite Handler

CSound* Song;

long int start = GetTickCount();								//Frames-Per-Second Controller

int Game_Init(HWND hwnd)
{
	result = D3DXCreateSprite(d3ddev, &SpHd);					//Create Sprite Handler
	if (result != D3D_OK)
	{
		return 0;
	}

	D3DXCreateFont(												//Font Creation
		d3ddev,
		30,
		0, 
		FW_BOLD,
		0, 
		FALSE, 
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"),
		&title_font );

	D3DXCreateFont(
		d3ddev,
		23,
		0, 
		FW_BOLD,
		0, 
		FALSE, 
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"),
		&game_font );

	D3DXCreateFont(
		d3ddev,
		23,
		0, 
		FW_BOLD,
		0, 
		FALSE, 
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"),
		&view_font );

	D3DXCreateFont(
		d3ddev,
		45,
		0, 
		FW_BOLD,
		0, 
		FALSE, 
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"),
		&speed_font );

	D3DXCreateFont(
		d3ddev,
		40,
		0, 
		FW_BOLD,
		0, 
		FALSE, 
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"),
		&speed_select_font );

	D3DXCreateFont(
		d3ddev,
		60,
		0, 
		FW_BOLD,
		0, 
		FALSE, 
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"),
		&name_font );

	D3DXCreateFont(
		d3ddev,
		40,
		0, 
		FW_BOLD,
		0, 
		FALSE, 
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"),
		&name_select_font );

	D3DXCreateFont(
		d3ddev,
		35,
		0, 
		FW_BOLD,
		0, 
		FALSE, 
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"),
		&help_font );

	Song = LoadSound("music.wav");
	if (Song == NULL)
	{
		return 0;
	}

	back = LoadSurface("Background.bmp", NULL);					//Create Surfaces

	menu_box = LoadTexture(										//Create Textures
		"Menu Box.bmp", 
		D3DCOLOR_XRGB(255, 255, 255));

	menu_header = LoadTexture(
		"Menu Header.bmp", 
		D3DCOLOR_XRGB(255, 255, 255));

	menu_word_view = LoadTexture(
		"Menu Button1.bmp", 
		D3DCOLOR_XRGB(255, 255, 255));

	menu_speed_change = LoadTexture(
		"Menu Button2.bmp", 
		D3DCOLOR_XRGB(255, 255, 255));

	menu_mute_sounds = LoadTexture(
		"Menu Button3.bmp", 
		D3DCOLOR_XRGB(255, 255, 255));

	menu_exit_menu = LoadTexture(
		"Menu Button4.bmp", 
		D3DCOLOR_XRGB(255, 255, 255));

	menu_exit_game = LoadTexture(
		"Menu Button5.bmp", 
		D3DCOLOR_XRGB(255, 255, 255));

	menu_fader = LoadTexture(
		"background.bmp",
		D3DCOLOR_XRGB(100, 100, 100));

	introduction = LoadTexture(
		"Intro.tga", 
		D3DCOLOR_XRGB(5, 255, 255));

	title = LoadTexture(
		"Title.bmp", 
		D3DCOLOR_XRGB(0, 0, 0));

	arrow = LoadTexture(
		"Arrow.bmp",
		D3DCOLOR_XRGB(255, 255, 255));

	HUD_out = LoadTexture(
		"OutIF.tga", 
		D3DCOLOR_XRGB(255, 255, 255));

	HUD_in = LoadTexture(
		"InIF.tga", 
		D3DCOLOR_XRGB(255, 255, 255));

	view_arrow1 = LoadTexture(
		"Word Viewer Arrow 1.bmp", 
		D3DCOLOR_XRGB(0, 0, 0));

	view_arrow2 = LoadTexture(
		"Word Viewer Arrow 2.bmp", 
		D3DCOLOR_XRGB(0, 0, 0));

	view_bg = LoadTexture(
		"Word Viewer BG.bmp", 
		D3DCOLOR_XRGB(0, 0, 0));

	view_slider = LoadTexture(
		"Word Viewer Slider.bmp", 
		D3DCOLOR_XRGB(0, 0, 0));

	view_blockers = LoadTexture(
		"Blockers.bmp", 
		D3DCOLOR_XRGB(255, 255, 255));

	anime = LoadTexture(
		"Anime.tga", 
		D3DCOLOR_XRGB(255, 0, 255));

	ct = LoadTexture(
		"Continue.tga", 
		D3DCOLOR_XRGB(255, 0, 255));

	eend = LoadTexture(
		"End.tga", 
		D3DCOLOR_XRGB(255, 0, 255));

	triton = LoadTexture(
		"Triton.tga", 
		D3DCOLOR_XRGB(255, 0, 255));

	hamburger = LoadTexture(
		"Hamburger.tga", 
		D3DCOLOR_XRGB(255, 0, 255));

	koala1 = LoadTexture(
		"Koala.tga", 
		D3DCOLOR_XRGB(255, 0, 255));

	koala2 = LoadTexture(
		"Koala2.tga", 
		D3DCOLOR_XRGB(255, 0, 255));

	apoc = LoadTexture(
		"Apocalypse.tga", 
		D3DCOLOR_XRGB(255, 0, 255));

	ufo = LoadTexture(
		"UFO.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	balloons = LoadTexture(
		"Balloons.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	boat = LoadTexture(
		"Boat.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	eyes = LoadTexture(
		"Eyes.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	heart = LoadTexture(
		"Heart.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	hotel = LoadTexture(
		"Hotel.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	housein = LoadTexture(
		"HouseIn.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	loading = LoadTexture(
		"Loading.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	mansion = LoadTexture(
		"Mansion.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	map = LoadTexture(
		"Map.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	medal = LoadTexture(
		"Medal.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	party = LoadTexture(
		"Party.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	rest1 = LoadTexture(
		"R1.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	rest2 = LoadTexture(
		"R2.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	sunny = LoadTexture(
		"Sunny.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	rainy = LoadTexture(
		"Thunderstorm.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	tombstone = LoadTexture(
		"Tombstone.tga", 
		D3DCOLOR_XRGB(255, 0, 255));
	
	yale = LoadTexture(
		"Yale.tga", 
		D3DCOLOR_XRGB(255, 0, 255));

	forest = LoadTexture("Boat.tga", NULL);

	Forest.Change_Texture(forest);

	Anime.Change_Texture(anime);
	Ct.Change_Texture(ct);
	End.Change_Texture(eend);
	Triton.Change_Texture(triton);
	Hamburger.Change_Texture(hamburger);
	Koala1.Change_Texture(koala1);
	Koala2.Change_Texture(koala2);
	Apoc.Change_Texture(apoc);
	Ufo.Change_Texture(ufo);
	Balloons.Change_Texture(balloons);
	Boat.Change_Texture(boat);
	Eyes.Change_Texture(eyes);
	Heart.Change_Texture(heart);
	Hotel.Change_Texture(hotel);
	Housein.Change_Texture(housein);
	Loading.Change_Texture(loading);
	Mansion.Change_Texture(mansion);
	Map.Change_Texture(map);
	Medal.Change_Texture(medal);
	Party.Change_Texture(party);
	Rest1.Change_Texture(rest1);
	Rest2.Change_Texture(rest2);
	Sunny.Change_Texture(sunny);
	Rainy.Change_Texture(rainy);
	Tombstone.Change_Texture(tombstone);
	Yale.Change_Texture(yale);

	if (!Init_DirectInput(hwnd))								//Load DirectInput
	{
		MessageBox(hwnd, "Error", "Error", MB_OK);
		return 0;
	}

	if (!Init_Mouse(hwnd))										//Load Mouse
	{
		return 0;
	}

	if (!Init_Keyboard(hwnd))									//Load Keyboard
	{
		return 0;
	}

	return 1;
}

string String_Combine(char* string1, char* string2)
{
    string first(string1);
	string second(string2);
    string combined = first + second;

	return combined;
}

char* String_Convert(string str)
{
	char *buf;
	buf = (char*)GlobalAlloc(GPTR, str.size());

	strcpy(buf, str.c_str());

	return buf;
}

void Introduction()
{
	if (intro_status == 1)
	{
		intro_count++;
	}

	D3DXVECTOR3 position ((float)0, (float)0, 0);

	if (intro_status == 1 && intro_alpha >= 0)
	{
		SpHd->Draw(
			introduction, 
			NULL, 
			NULL, 
			&position, 
			D3DCOLOR_ARGB(intro_alpha, 255, 255, 255));
	}

	if (intro_status == 1)
	{
		intro_alpha = intro_alpha + intro_ainc;
		intro_alpha = intro_alpha - intro_adec;

		if (intro_alpha == 50)
		{
			Song->Play();
		}

		if (intro_alpha >= 255)
		{
			intro_ainc = 0;
			intro_alpha = 255;
		}

		if (intro_count >= 200)
		{
			intro_adec = 13;
		}

		if (intro_alpha <= 0)
		{
			intro_adec = 0;
			intro_alpha = 0;
		}

		if (intro_alpha <= 0 && intro_count > 200)
		{
			intro_status = 0;
			title_status = 1;
		}
	}
}

void Title_Screen()
{
	if (title_status == 1)
	{
		title_count++;
	}

	D3DXVECTOR3 position ((float)0, (float)0, 0);

	if (title_count == 60 && title_status == 1)
	{
		title_ainc = 4;
	}

	if (title_status == 1 && title_alpha >= 255)
	{
		title_ainc = 0;
		title_alpha = 255;
	}

	if (title_count >= 205 && title_status == 1)
	{
		title_button_status = 1;
	}

	if (title_button_status == 1 && title_status == 1)
	{
		if (Key_Down(DIK_RETURN))
		{
			title_adec = 1;
			title_letters_adec = 4;
			title_letters_ainc = 0;
		}
	}

	if (title_status == 1 && title_letters_alpha >= 255)
	{
		title_letters_ainc = 0;
		title_letters_alpha = 255;
	}

	if (title_status == 1 && title_letters_alpha <= 0 && title_count >= 250)
	{
		title_letters_alpha = 0;
		title_letters_adec = 0;
		title_letters_active = 0;
	}

	if (title_count > 200 && title_alpha <= 0 && title_status == 1)
	{
		title_adec = 0;
		title_alpha = 0;
	}

	if (title_status == 1 && title_count > 205 && title_letters_alpha <= 0)
	{
		title_letters_adec = 0;
		title_letters_alpha = 0;
	}

	if (title_count > 250 && title_alpha <= 0 && title_status == 1)
	{
		title_status = 0;
		speed_status = 1;
	}

	if (title_status == 1)
	{	
		SpHd->Draw(
			title, 
			NULL, 
			NULL, 
			&position, 
			D3DCOLOR_ARGB(title_alpha, 255, 255, 255));

		title_alpha = title_alpha + title_ainc;
		title_alpha = title_alpha - title_adec;	
	}

	if (title_letters_active == 1 && title_count >= 180 && title_status == 1)
	{
		RECT rect;
		rect.top = 400;
		rect.left = 200;
		rect.bottom = 600;
		rect.right = 600;

		title_font->DrawText(
			NULL, 
			title_string, 
			-1, 
			&rect, 
			DT_CENTER, 
			D3DCOLOR_ARGB(title_letters_alpha, 255, 255, 255));

		title_letters_alpha = title_letters_alpha + title_letters_ainc;
		title_letters_alpha = title_letters_alpha - title_letters_adec;
	}
}

void Speed_Select()
{
	if (speed_status == 1)
	{
		speed_count++;
	}

	if (speed_status == 1 && speed_count == 60)
	{
		help_ainc = 3;
	}

	if (speed_status == 1 && help_alpha >= 255)
	{
		help_ainc = 0;
		help_alpha = 255;
	}

	if (speed_status == 1 && help_alpha <= 0)
	{
		help_adec = 0;
		help_alpha = 0;
	}

	if (speed_alpha >= 255 && speed_status == 1)
	{
		speed_ainc = 0;
		speed_alpha = 255;
	}

	if (speed_alpha <= 0 && speed_status == 1)
	{
		speed_adec = 0;
		speed_alpha = 0;
	}

	if (speed_status == 1 && speed_count == 130)
	{
		speed_button_status = 0;
	}

	if (speed_status == 1 && speed_count == 180)
	{
		game_font_active = 1;
		game_font_status = 1;
	}

	if (speed_status == 1 && speed_count > 140 && help_counter < strlen(help_string))
	{
		if (speed_pick == 1)
		{
			if (speed_count % 7 == 0 && game_font_active == 1)
			{
				help_counter++;
			}
		}

		if (speed_pick == 2)
		{
			if (speed_count % 5 == 0 && game_font_active == 1)
			{
				help_counter++;
			}
		}

		if (speed_pick == 3)
		{
			if (speed_count % 4 == 0 && game_font_active == 1)
			{
				help_counter++;
			}
		}

		if (speed_pick == 4)
		{
			if (speed_count % 3 == 0 && game_font_active == 1)
			{
				help_counter++;
			}
		}

		if (speed_pick == 5)
		{
			if (speed_count % 2 == 0 && game_font_active == 1)
			{
				help_counter++;
			}
		}
	}

	if (speed_status == 1 && game_font_status == 1 && game_font_alpha <= 0)
	{
		game_font_adec = 0;
		game_font_alpha = 0;
	}

	if (speed_status == 1 && speed_button_status == 1)
	{
		if (Key_Down(DIK_RIGHT) && speed_pick != 5 && speed_count_keeper + 12 < speed_count)
		{
			speed_pick++;
			speed_count_keeper = speed_count;
			help_counter = 0;
		}

		if (Key_Down(DIK_LEFT) && speed_pick != 1 && speed_count_keeper + 12 < speed_count)
		{
			speed_pick--;
			speed_count_keeper = speed_count;
			help_counter = 0;
		}
	}

	if (speed_status == 1 && speed_button_status == 1)
	{
		if (Key_Down(DIK_RETURN))
		{
				speed_input = speed_pick;
				speed_button_status = 2;
				help_adec = 5;
				speed_adec = 3;
				game_font_active = 0;
				game_font_adec = 5;
		}
	}

	if (speed_status == 1 && speed_button_status == 1)
	{
		if (speed_pick == 1)
		{
			Speed_Select_Sub(speed_main_alpha, speed_others_alpha, speed_others_alpha, speed_others_alpha, speed_others_alpha);
		}
		
		if (speed_pick == 2)
		{
			Speed_Select_Sub(speed_others_alpha, speed_main_alpha, speed_others_alpha, speed_others_alpha, speed_others_alpha);
		}

		if (speed_pick == 3)
		{
			Speed_Select_Sub(speed_others_alpha, speed_others_alpha, speed_main_alpha, speed_others_alpha, speed_others_alpha);
		}

		if (speed_pick == 4)
		{
			Speed_Select_Sub(speed_others_alpha, speed_others_alpha, speed_others_alpha, speed_main_alpha, speed_others_alpha);
		}

		if (speed_pick == 5)
		{
			Speed_Select_Sub(speed_others_alpha, speed_others_alpha, speed_others_alpha, speed_others_alpha, speed_main_alpha);
		}
	}

	if (speed_status == 1 && speed_button_status == 0)
	{
		if (speed_main_alpha < 255)
		{
			speed_main_alpha = speed_main_alpha + speed_main_ainc;
		}

		if (speed_main_alpha >= 255)
		{
			speed_main_alpha = 255;
			speed_main_ainc = 0;
		}

		if (speed_main_alpha <= 0)
		{
			speed_main_adec = 0;
			speed_main_alpha = 0;
		}

		if (speed_others_alpha < 120)
		{
			speed_others_alpha = speed_others_alpha + speed_others_ainc;
		}

		Speed_Select_Sub(speed_others_alpha, speed_others_alpha, speed_main_alpha, speed_others_alpha, speed_others_alpha);

		if (speed_others_alpha == 120 && speed_main_alpha == 255)
		{
			speed_button_status = 1;
		}
	}

	if (speed_status == 1 && speed_button_status == 2)
	{
		if (speed_pick == 1)
		{
			Speed_Select_Sub(speed_main_alpha, speed_others_alpha, speed_others_alpha, speed_others_alpha, speed_others_alpha);
		}

		if (speed_pick == 2)
		{
			Speed_Select_Sub(speed_others_alpha, speed_main_alpha, speed_others_alpha, speed_others_alpha, speed_others_alpha);
		}

		if (speed_pick == 3)
		{
			Speed_Select_Sub(speed_others_alpha, speed_others_alpha, speed_main_alpha, speed_others_alpha, speed_others_alpha);
		}

		if (speed_pick == 4)
		{
			Speed_Select_Sub(speed_others_alpha, speed_others_alpha, speed_others_alpha, speed_main_alpha, speed_others_alpha);
		}

		if (speed_pick == 5)
		{
			Speed_Select_Sub(speed_others_alpha, speed_others_alpha, speed_others_alpha, speed_others_alpha, speed_main_alpha);
		}

		if (speed_main_alpha > 0)
		{
			speed_main_alpha = speed_main_alpha - speed_main_adec;
		}

		if (speed_others_alpha > 0)
		{
			speed_others_alpha = speed_others_alpha - speed_others_adec;
		}

		if (speed_alpha > 0)
		{
			speed_alpha = speed_alpha - speed_adec;
		}

		if (speed_others_alpha == 0 && speed_main_alpha == 0 && speed_alpha == 0 && help_alpha == 0 && game_font_alpha == 0)
		{
			speed_button_status = 3;
			game_font_status = 0;
		}
	}

	if (speed_status == 1 && speed_count >= 40)
	{
		RECT rect;
		rect.top = 150;
		rect.left = 0;
		rect.bottom = 500;
		rect.right = 800;

		speed_font->DrawText(
		NULL, 
		speed_string, 
		-1, 
		&rect, 
		DT_CENTER, 
		D3DCOLOR_ARGB(speed_alpha, 255, 255, 255));

		speed_alpha = speed_alpha + speed_ainc;
	}


	if (speed_status == 1 && speed_count >= 140 && game_font_status == 1)
	{
		RECT rect;
		rect.top = 450;
		rect.left = 146;
		rect.bottom = 600;
		rect.right = 700;

		game_font->DrawText(
		NULL, 
		help_string, 
		help_counter, 
		&rect, 
		DT_LEFT, 
		D3DCOLOR_ARGB(game_font_alpha, 240, 240, 255));

		game_font_alpha = game_font_alpha - game_font_adec;
	}


	if (speed_status == 1 && speed_count > 80)
	{
		RECT rect;
		rect.top = 225;
		rect.left = 0;
		rect.bottom = 500;
		rect.right = 800;

		help_font->DrawText(
		NULL, 
		"(Using the arrow keys)", 
		-1, 
		&rect, 
		DT_CENTER, 
		D3DCOLOR_ARGB(help_alpha, 200, 200, 200));

		help_alpha = help_alpha + help_ainc;
		help_alpha = help_alpha - help_adec;
	}

	if (speed_button_status == 3)
	{
			speed_status = 0;
			name_status = 1;
	}
}

void Speed_Select_Sub(int alpha1, int alpha2, int alpha3, int alpha4, int alpha5)
{
		RECT rect1;
		rect1.top = 300;
		rect1.left = 150;
		rect1.bottom = 600;
		rect1.right = 250;

		RECT rect2;
		rect2.top = 300;
		rect2.left = 250;
		rect2.bottom = 600;
		rect2.right = 350;

		RECT rect3;
		rect3.top = 300;
		rect3.left = 350;
		rect3.bottom = 600;
		rect3.right = 450;

		RECT rect4;
		rect4.top = 300;
		rect4.left = 450;
		rect4.bottom = 600;
		rect4.right = 550;

		RECT rect5;
		rect5.top = 300;
		rect5.left = 550;
		rect5.bottom = 600;
		rect5.right = 650;

		speed_select_font->DrawText(
		NULL, 
		"1", 
		-1, 
		&rect1, 
		DT_CENTER, 
		D3DCOLOR_ARGB(alpha1, 255, 255, 255));

		speed_select_font->DrawText(
		NULL, 
		"2", 
		-1, 
		&rect2, 
		DT_CENTER, 
		D3DCOLOR_ARGB(alpha2, 255, 255, 255));

		speed_select_font->DrawText(
		NULL, 
		"3", 
		-1, 
		&rect3, 
		DT_CENTER, 
		D3DCOLOR_ARGB(alpha3, 255, 255, 255));

		speed_select_font->DrawText(
		NULL, 
		"4", 
		-1, 
		&rect4, 
		DT_CENTER, 
		D3DCOLOR_ARGB(alpha4, 255, 255, 255));

		speed_select_font->DrawText(
		NULL, 
		"5", 
		-1, 
		&rect5, 
		DT_CENTER, 
		D3DCOLOR_ARGB(alpha5, 255, 255, 255));
}

void Name_Select()
{
	if (name_status == 1)
	{
		name_count++;
	}

	if (name_status == 1 && name_count == 120)
	{
		help_ainc = 3;
	}

	if (name_status == 1 && help_alpha >= 255)
	{
		help_ainc = 0;
		help_alpha = 255;
	}

	if (name_status == 1 && help_alpha <= 0)
	{
		help_adec = 0;
		help_alpha = 0;
	}

	if (name_status == 1)
	{
		if (name_alpha <= 0)
		{
			name_adec = 0;
			name_alpha = 0;
		}

		if (name_input_alpha <= 0)
		{
			name_input_adec = 0;
			name_input_alpha = 0;
		}
	}

	if (name_status == 1 && name_count > 120)
	{
		RECT rect;
		rect.top = 450;
		rect.left = 0;
		rect.bottom = 600;
		rect.right = 800;

		help_alpha = help_alpha + help_ainc;
		help_alpha = help_alpha - help_adec;

		help_font->DrawText(
		NULL, 
		"Press Enter When You're Done", 
		-1, 
		&rect, 
		DT_CENTER, 
		D3DCOLOR_ARGB(help_alpha, 200, 200, 200));
	}

	if (name_status == 1 && name_count > 235)
	{
		RECT rect;
		rect.top = 320;
		rect.left = 0;
		rect.bottom = 600;
		rect.right = 800;

		name_select_font->DrawText(
		NULL, 
		name_input_string, 
		-1, 
		&rect, 
		DT_CENTER, 
		D3DCOLOR_ARGB(name_input_alpha, 255, 255, 255));

		name_input_alpha = name_input_alpha - name_input_adec;

		if (name_count == 240)
		{
			name_button_status = 1;
		}
	}

	if (name_status == 1 && name_count > 90)
	{
		RECT rect;
		rect.top = 150;
		rect.left = 0;
		rect.bottom = 500;
		rect.right = 800;

		if (name_alpha >= 255)
		{
			name_ainc = 0;
			name_alpha = 255;
		}

		if (name_alpha <= 0)
		{
			name_adec = 0;
			name_alpha = 0;
		}

		name_font->DrawText(
		NULL, 
		name_string, 
		-1, 
		&rect, 
		DT_CENTER, 
		D3DCOLOR_ARGB(name_alpha, 255, 255, 255));

		name_alpha = name_alpha + name_ainc;
		name_alpha = name_alpha - name_adec;
	}

	if (name_status == 1 && name_button_status == 1)
	{
		if (strlen(name_input_string) <= 15)
		{
			if (Key_Down(DIK_BACKSPACE) && name_count_keeper + 8 < name_count && strlen(name_input_string) != 0)
			{
				name_count_keeper = name_count;
				string holder(name_input_string);
				holder.erase(strlen(name_input_string) - 1, strlen(name_input_string));
				name_input_string = String_Convert(holder);
			}

			if (Key_Down(DIK_A) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "A");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_A) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "a");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}

			if (Key_Down(DIK_B) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "B");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_B) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "b");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}

			if (Key_Down(DIK_C) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "C");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_C) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "c");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
	
			if (Key_Down(DIK_D) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "D");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_D) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "d");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
	
			if (Key_Down(DIK_E) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "E");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_E) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "e");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
	
			if (Key_Down(DIK_F) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)	
			{
				name_string_holder = String_Combine(name_input_string, "F");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_F) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "f");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}

			if (Key_Down(DIK_G) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "G");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_G) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "g");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}

			if (Key_Down(DIK_H) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "H");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_H) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "h");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}	
	
			if (Key_Down(DIK_I) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "I");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_I) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "i");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}	
	
			if (Key_Down(DIK_J) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "J");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_J) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "j");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
	
			if (Key_Down(DIK_K) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "K");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_K) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "k");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}	

			if (Key_Down(DIK_L) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "L");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_L) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "l");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
	
			if (Key_Down(DIK_M) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "M");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_M) && name_count_keeper + 8 < name_count)
			{	
				name_string_holder = String_Combine(name_input_string, "m");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}

			if (Key_Down(DIK_N) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "N");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_N) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "n");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}	

			if (Key_Down(DIK_O) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "O");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_O) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "o");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}	

			if (Key_Down(DIK_P) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "P");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_P) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "p");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}

			if (Key_Down(DIK_Q) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "Q");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_Q) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "q");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
	
			if (Key_Down(DIK_R) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "R");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_R) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "r");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}

			if (Key_Down(DIK_S) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "S");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_S) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "s");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
	
			if (Key_Down(DIK_T) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "T");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_T) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "t");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
	
			if (Key_Down(DIK_U) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "U");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_U) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "u");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
	
			if (Key_Down(DIK_V) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "V");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_V) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "v");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
	
			if (Key_Down(DIK_W) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "W");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_W) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "w");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
	
			if (Key_Down(DIK_X) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "X");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_X) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "x");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
	
			if (Key_Down(DIK_Y) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "Y");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_Y) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "y");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
	
			if (Key_Down(DIK_Z) && (Key_Down(DIK_LSHIFT) || (Key_Down(DIK_RSHIFT))) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "Z");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}
			else if (Key_Down(DIK_Z) && name_count_keeper + 8 < name_count)
			{
				name_string_holder = String_Combine(name_input_string, "z");
				name_input_string = String_Convert(name_string_holder);
				name_count_keeper = name_count;
			}

			if (Key_Down(DIK_RETURN) && name_button_status == 1)
			{
				name_adec = 5;
				name_input_adec = 3;
				help_adec = 5;
				name_button_status = 0;
				VN_status = 1;
				HUD_status = 1;
				VN_active = 1;
			}
		}
	}

	if (name_status == 1)
	{
		if (name_input_alpha == 0 && name_alpha == 0 && help_alpha == 0)
		{
			name_status = 0;
			game_font_alpha = 255;
			game_font_ainc = 0;
			game_font_adec = 0;
			game_font_active = 0;
			game_font_status = 0;
		}
	}
}

int HUD_Display(int x)
{
	if (x != 0)
	{
		if (HUD_status == 1 && HUD_count < 0)
		{
			HUD_count++;
		}

		D3DXVECTOR3 out_position ((float)0, (float)0, 0);
		D3DXVECTOR3 in_position ((float)0, (float)0, 0);

		if (HUD_status == 1)
		{
			SpHd->Draw(
				HUD_out, 
				NULL, 
				NULL, 
				&out_position, 
				D3DCOLOR_ARGB(HUD_out_alpha, 255, 255, 255));

			SpHd->Draw(
				HUD_in, 
				NULL, 
				NULL, 
				&in_position, 
				D3DCOLOR_ARGB(HUD_in_alpha, 255, 255, 255));
		}

		if (HUD_status == 1 && HUD_count >= 0)
		{
			HUD_out_alpha = HUD_out_alpha + HUD_out_ainc;
			HUD_in_alpha = HUD_in_alpha + HUD_in_ainc;

			if (HUD_out_alpha >= 255)
			{
				HUD_out_ainc = 0;
				HUD_out_alpha = 255;
			}
	
			if (HUD_in_alpha >= 170)
			{
				HUD_in_ainc = 0;
				HUD_in_alpha = 170;
			}

			if (HUD_out_alpha <= 0)
			{
				HUD_out_adec = 0;
				HUD_out_alpha = 0;
			}

			if (HUD_in_alpha <= 0)
			{
				HUD_in_adec = 0;
				HUD_in_alpha = 0;
			}

			if (HUD_in_alpha == 170 && HUD_out_alpha == 255)
			{
				HUD_done = 1;
				return 1;
			}

			if (HUD_in_alpha != 170 || HUD_out_alpha != 255)
			{
				return 0;
			}
		}
	}

			if (HUD_in_alpha == 170 && HUD_out_alpha == 255)
			{
				return 1;
			}

			if (HUD_in_alpha != 170 || HUD_out_alpha != 255)
			{
				return 0;
			}
}

int HUD_Vanish(int x)
{
	D3DXVECTOR3 out_position ((float)0, (float)0, 0);
	D3DXVECTOR3 in_position ((float)0, (float)0, 0);

	SpHd->Draw(
		HUD_out, 
		NULL, 
		NULL, 
		&out_position, 
		D3DCOLOR_ARGB(HUD_out_alpha, 255, 255, 255));

	SpHd->Draw(
		HUD_in, 
		NULL, 
		NULL, 
		&in_position, 
		D3DCOLOR_ARGB(HUD_in_alpha, 255, 255, 255));
	
	HUD_out_alpha = HUD_out_alpha - HUD_out_adec;
	HUD_in_alpha = HUD_in_alpha - HUD_in_adec;

	if (HUD_out_alpha >= 255)
	{
		HUD_out_ainc = 0;
		HUD_out_alpha = 0;
	}

	if (HUD_in_alpha >= 170)
	{
		HUD_in_ainc = 0;
		HUD_in_alpha = 170;
	}

	if (HUD_out_alpha <= 0)
	{
		HUD_out_adec = 0;
		HUD_out_alpha = 0;
	}

	if (HUD_in_alpha <= 0)
	{
		HUD_in_adec = 0;
		HUD_in_alpha = 0;
		HUD_status = 0;
		return 1;
	}

	return 0;
}

void HUD_Reset()
{
	HUD_status = 1;
	HUD_out_alpha = 0;
	HUD_out_ainc = 3;
	HUD_out_adec = 1;
	HUD_in_alpha = 0;
	HUD_in_ainc = 3;
	HUD_in_adec = 1;
	HUD_count = 0;
	HUD_done = 0;

	word_tick = 1;
	word_count = 0;
	word_count_keeper = 0;
}

Background::Background(int X, int Y)
{
	alpha = 0;
	load = 1;
	x = X;
	y = Y;
	D3DXVECTOR3 Position ((float)x, (float)y, 0);
	position = Position;
}

void Background::Change_Texture(LPDIRECT3DTEXTURE9 Texture)
{
	texture = Texture;
}

void Background::Reload()
{
	load = 1;
}

int Background::Display(int Ainc, int Delay)
{
	if (load == 1)
	{
		ainc = Ainc;
		delay = Delay;
		load = 0;
	}

	if (delay != 0)
	{
		delay--;
	}

	SpHd->Draw(
		texture, 
		NULL, 
		NULL, 
		&position, 
		D3DCOLOR_ARGB(alpha, 255, 255, 255));

	if (delay == 0)
	{
		alpha = alpha + ainc;
	}

	if (alpha >= 255)
	{
		ainc = 0;
		alpha = 255;
	}

	if (alpha == 255)
	{
		return 1;
	}

	if (alpha != 255)
	{
		return 0;
	}
}

int Background::Vanish(int Adec, int Delay)
{
	if (load == 1)
	{
		adec = Adec;
		delay = Delay;
		load = 0;
	}

	if (delay != 0)
	{
		delay--;
	}

	SpHd->Draw(
		texture, 
		NULL, 
		NULL, 
		&position, 
		D3DCOLOR_ARGB(alpha, 255, 255, 255));

	if (delay == 0)
	{
		alpha = alpha - adec;
	}

	if (alpha <= 0)
	{
		adec = 0;
		alpha = 0;
	}

	if (alpha == 0)
	{
		return 1;
	}

	if (alpha != 0)
	{
		return 0;
	}
}

void Background::Reset()
{
	load = 1;
	alpha = 0;
}

Character::Character(int X, int Y)
{
	alpha1 = 0;
	alpha2 = 255;
	load = 1;
	repose = 1;
	x = X;
	y = Y;
	D3DXVECTOR3 Position1 ((float)x, (float)y, 0);
	position1 = Position1;
	D3DXVECTOR3 Position2 ((float)x, (float)y, 0);
	position2 = Position2;
}

void Character::Change_Texture(LPDIRECT3DTEXTURE9 Texture, int Number)
{
	if (Number == 1)
	{
		texture1 = Texture;
	}

	if (Number == 2)
	{
		texture2 = Texture;
	}

	if (Number == 3)
	{
		texture3 = Texture;
	}

	if (Number == 4)
	{
		texture4 = Texture;
	}

	if (Number == 5)
	{
		texture5 = Texture;
	}

	if (Number == 6)
	{
		texture6 = Texture;
	}

	if (Number == 7)
	{
		texture7 = Texture;
	}

	if (Number == 8)
	{
		texture8 = Texture;
	}

	if (Number == 9)
	{
		texture9 = Texture;
	}
}

void Character::Reload()
{
	load = 1;
	vanish_status = 1;
}

void Character::Prepare()
{
	repose = 1;
}

void Character::Relocate(int X, int Y)
{
	if (repose == 1)
	{
		D3DXVECTOR3 Position1 ((float)X, (float)Y, 0);
		position2 = position1;
		position1 = Position1;

		alpha1 = 0;
		alpha2 = 255;

		repose = 0;
	}
}

void Character::Reset()
{
	alpha1 = 0;
	alpha2 = 255;
	load = 1;
	repose = 1;
	vanish_status = 0;
}

int Character::Display(int Ainc, int Delay, int Number)
{
	if (load == 1)
	{
		ainc = Ainc;
		delay = Delay;
		load = 0;
	}

	if (delay != 0)
	{
		delay--;
	}

	if (Number == 1)
	{
		SpHd->Draw(
			texture1, 
			NULL, 
			NULL, 
			&position1, 
			D3DCOLOR_ARGB(alpha1, 255, 255, 255));
	}

	if (Number == 2)
	{
		SpHd->Draw(
			texture2, 
			NULL, 
			NULL, 
			&position1, 
			D3DCOLOR_ARGB(alpha1, 255, 255, 255));
	}

	if (Number == 3)
	{
		SpHd->Draw(
			texture3, 
			NULL, 
			NULL, 
			&position1, 
			D3DCOLOR_ARGB(alpha1, 255, 255, 255));
	}

	if (Number == 4)
	{
		SpHd->Draw(
			texture4, 
			NULL, 
			NULL, 
			&position1, 
			D3DCOLOR_ARGB(alpha1, 255, 255, 255));
	}

	if (Number == 5)
	{
		SpHd->Draw(
			texture5, 
			NULL, 
			NULL, 
			&position1, 
			D3DCOLOR_ARGB(alpha1, 255, 255, 255));
	}

	if (Number == 6)
	{
		SpHd->Draw(
			texture6, 
			NULL, 
			NULL, 
			&position1, 
			D3DCOLOR_ARGB(alpha1, 255, 255, 255));
	}

	if (Number == 7)
	{
		SpHd->Draw(
			texture7, 
			NULL, 
			NULL, 
			&position1, 
			D3DCOLOR_ARGB(alpha1, 255, 255, 255));
	}

	if (Number == 8)
	{
		SpHd->Draw(
			texture8, 
			NULL, 
			NULL, 
			&position1, 
			D3DCOLOR_ARGB(alpha1, 255, 255, 255));
	}

	if (Number == 9)
	{
		SpHd->Draw(
			texture9, 
			NULL, 
			NULL, 
			&position1, 
			D3DCOLOR_ARGB(alpha1, 255, 255, 255));
	}

	if (delay == 0)
	{
		alpha1 = alpha1 + ainc;
	}

	if (alpha1 >= 255)
	{
		ainc = 0;
		alpha1 = 255;
	}

	if (alpha1 == 255)
	{
		return 1;
	}

	if (alpha1 != 255)
	{
		return 0;
	}
}

int Character::Vanish(int Adec, int Delay, int Number)
{
	if (load == 1)
	{
		adec = Adec;
		delay = Delay;
	}

	if (delay != 0)
	{
		delay--;
	}

	if (vanish_status == 1)
	{
		if (Number == 1)
		{
			SpHd->Draw(
				texture1, 
				NULL, 
				NULL, 
				&position2, 
				D3DCOLOR_ARGB(alpha2, 255, 255, 255));
		}

		if (Number == 2)
		{
			SpHd->Draw(
				texture2, 
				NULL, 
				NULL, 
				&position2, 
				D3DCOLOR_ARGB(alpha2, 255, 255, 255));
		}

		if (Number == 3)
		{
			SpHd->Draw(
				texture3, 
				NULL, 
				NULL, 
				&position2, 
				D3DCOLOR_ARGB(alpha2, 255, 255, 255));
		}

		if (Number == 4)
		{
			SpHd->Draw(
				texture4, 
				NULL, 
				NULL, 
				&position2, 
				D3DCOLOR_ARGB(alpha2, 255, 255, 255));
		}

		if (Number == 5)
		{
				SpHd->Draw(
				texture5, 
				NULL, 
				NULL, 
				&position2, 
				D3DCOLOR_ARGB(alpha2, 255, 255, 255));
		}

		if (Number == 6)
		{
			SpHd->Draw(
				texture6, 
				NULL, 
				NULL, 
				&position2, 
				D3DCOLOR_ARGB(alpha2, 255, 255, 255));
		}

		if (Number == 7)
		{
			SpHd->Draw(
				texture7, 
				NULL, 
				NULL, 
				&position2, 
				D3DCOLOR_ARGB(alpha2, 255, 255, 255));
		}

		if (Number == 8)
		{
			SpHd->Draw(
				texture8, 
				NULL, 
				NULL, 
				&position2, 
				D3DCOLOR_ARGB(alpha2, 255, 255, 255));
		}

		if (Number == 9)
		{
			SpHd->Draw(
				texture9, 
				NULL, 
				NULL, 
				&position2, 
				D3DCOLOR_ARGB(alpha2, 255, 255, 255));
		}
	}

	if (delay == 0)
	{
		alpha2 = alpha2 - adec;
	}

	if (alpha2 <= 0)
	{
		adec = 0;
		alpha2 = 0;
	}

	if (alpha2 == 0)
	{
		return 1;
	}

	if (alpha2 != 0)
	{
		return 0;
	}
}

int Character::Move(int Movex, int Movey, int Move_time)
{
	movex = Movex;
	movey = Movey;
	move_time = Move_time;

	movex_tick = movex / move_time;
	movey_tick = movey / move_time;

	if (movex != 0)
	{
		movex = movex - movex_tick;
	}

	if (movey != 0)
	{
		movey = movey - movey_tick;
	}

	if (movex != 0)
	{
		x = x + movex_tick;
		D3DXVECTOR3 Position1 ((float)x, (float)y, 0);
		position1 = Position1;
	}

	if (movey != 0)
	{
		y = y + movey_tick;
		D3DXVECTOR3 Position1 ((float)x, (float)y, 0);
		position1 = Position1;
	}

	if (movex == 0 && movey == 0)
	{
		return 1;
	}

	if (movex != 0 || movey != 0)
	{
		return 0;
	}
}

int Word_Processor(char* words, char* name, int speed, int r, int g, int b, int choices)
{
	if (words_active == 1)
	{
		word_tick++;
	}

	if (speed == 1)
	{
		if (word_tick % 7 == 0 && word_count < strlen(words))
		{
			word_count++;
		}
	}

	if (speed == 2)
	{
		if (word_tick % 5 == 0 && word_count < strlen(words))
		{
			word_count++;
		}
	}

	if (speed == 3)
	{
		if (word_tick % 4 == 0 && word_count < strlen(words))
		{
			word_count++;
		}
	}

	if (speed == 4)
	{
		if (word_tick % 3 == 0 && word_count < strlen(words))
		{
			word_count++;
		}
	}

	if (speed == 5)
	{
		if (word_tick % 2 == 0 && word_count < strlen(words))
		{
			word_count++;
		}
	}

	if (speed == 0)
	{
		while (word_count < strlen(words))
		{
			word_count++;
		}
	}

	RECT rect;
	rect.top = 412;
	rect.left = 35;
	rect.bottom = 600;
	rect.right = 700;

	if (words_active == 1)
	{
		game_font->DrawText(
		SpHd, 
		name, 
		-1, 
		&rect, 
		DT_LEFT, 
		D3DCOLOR_XRGB(255, 255, 255));
	}

	RECT rect2;
	rect2.top = 474;
	rect2.left = 35;
	rect2.bottom = 570;
	rect2.right = 770;

	if (words_active == 1)
	{
		game_font->DrawText(
		SpHd, 
		words, 
		word_count, 
		&rect2, 
		DT_WORDBREAK, 
		D3DCOLOR_XRGB(r, g, b));
	}

	D3DXVECTOR3 position ((float)word_arrowx, (float)word_arrowy, 0);

	if (word_count == strlen(words))
	{
		SpHd->Draw(
			arrow, 
			NULL, 
			NULL, 
			&position, 
			D3DCOLOR_ARGB(255, 255, 255, 255));

		if (word_tick - 6 > word_count_keeper)
		{
			if (word_arrowy < 251)
			{
				word_arrowy++;
			}
			else
			{
				word_arrowy = 244;
			}
			word_count_keeper = word_tick;
		}
	}

	if (choices == 0)
	{
		if (Key_Down(DIK_SPACE) && word_count == strlen(words))
		{	
			if (VN_active == 1)
			{
				word_tick = 1;
				word_count = 0;
				word_count_keeper = 0;
				word_arrowy = 244;

				return 1;
			}
		}
	}

	if (choices == 1)
	{
		if (Key_Down(DIK_LEFT) && word_count == strlen(words))
		{
			if (VN_active == 1)
			{
				word_tick = 1;
				word_count = 0;
				word_count_keeper = 0;
				word_arrowy = 244;

				return 1;
			}
		}

		if (Key_Down(DIK_RIGHT) && word_count == strlen(words))
		{
			if (VN_active == 1)
			{
				word_tick = 1;
				word_count = 0;
				word_count_keeper = 0;
				word_arrowy = 244;

				return 2;
			}
		}
	}

	return 0;
}

int Menu(HWND hwnd)
{
	if (VN_status == 1)
	{
		if (Key_Down(DIK_ESCAPE))
		{
			if (fade_status == 0)
			{
				fade_status = 1;
				fade_vn = 1;

				VN_active = 0;
			}
		}
	}

	if (menu_status == 1)
	{
		menu_count++;

		if (VN_status != 1)
		{
			if (menu_pick == 1)
			{
				Menu_Sub(255,
					255,
					menu_main_alpha,
					menu_others_alpha,
					menu_others_alpha,
					menu_others_alpha,
					menu_others_alpha);
			}
		}

		if (VN_status != 1)
		{
			if (menu_pick == 2)
			{
				Menu_Sub(255,
					255,
					menu_others_alpha,
					menu_main_alpha,
					menu_others_alpha,
					menu_others_alpha,
					menu_others_alpha);
			}

			if (menu_pick == 3)
			{
				Menu_Sub(255,
					255,
					menu_others_alpha,
					menu_others_alpha,
					menu_main_alpha,
					menu_others_alpha,
					menu_others_alpha);
			}

			if (menu_pick == 4)
			{
				Menu_Sub(255,
					255,
					menu_others_alpha,
					menu_others_alpha,
					menu_others_alpha,
					menu_main_alpha,
					menu_others_alpha);
			}

			if (menu_pick == 5)
			{
				Menu_Sub(255,
					255,
					menu_others_alpha,
					menu_others_alpha,
					menu_others_alpha,
					menu_others_alpha,
					menu_main_alpha);
			}

			if (Key_Down(DIK_DOWN) && menu_pick != 5 && menu_count_keeper + 12 < menu_count)
			{
				if (menu_active == 1)
				{
					menu_pick++;
					menu_count_keeper = menu_count;
				}
			}

			if (Key_Down(DIK_UP) && menu_pick != 1 && menu_count_keeper + 12 < menu_count)
			{
				if (menu_active == 1)
				{
					menu_pick--;
					menu_count_keeper = menu_count;
				}
			}

			if (Key_Down(DIK_RETURN) && VN_status != 1)
			{
				if (menu_active == 1)
				{
					if (menu_pick == 1)
					{
						fade_status = 1;
						fade_menu_view = 1;
					}

					if (menu_pick == 2)
					{
						fade_status = 1;
						fade_menu_speedc = 1;

						help_string = "That blueberry was the sweetest one I've ever eaten!";
						help_alpha = 0;
						help_ainc = 0;
						help_adec = 0;
						help_counter = 0;
					}

					if (menu_pick == 3)
					{
						if (sound_status == 1)
						{
							sound_status = 0;
						}
						else
						{
							sound_status = 1;
						}
					}

					if (menu_pick == 4)
					{
						fade_status = 1;
						fade_menu = 1;
					}

					if (menu_pick == 5)
					{
						PostMessage(hwnd, WM_DESTROY, 0, 0); 
					}

					menu_active = 0;
				}
			}
		}

		if (menu_status == 1)
		{
			return 1;
		}

		if (menu_status == 0)
		{
			return 0;
		}
	}

	return 0;
}

void Menu_Sub(int alpha1, int alpha2, int alpha3,
			 int alpha4, int alpha5, int alpha6, int alpha7)
{
	D3DXVECTOR3 position1 ((float)0, (float)0, 0);

	D3DXVECTOR3 position2 ((float)0, (float)0, 0);

	D3DXVECTOR3 position3 ((float)0, (float)0, 0);

	D3DXVECTOR3 position4 ((float)0, (float)0, 0);

	D3DXVECTOR3 position5 ((float)0, (float)0, 0);

	D3DXVECTOR3 position6 ((float)0, (float)0, 0);

	D3DXVECTOR3 position7 ((float)0, (float)0, 0);

	SpHd->Draw(
		menu_box, 
		NULL, 
		NULL, 
		&position1, 
		D3DCOLOR_ARGB(alpha1, 255, 255, 255));

	SpHd->Draw(
		menu_header, 
		NULL, 
		NULL, 
		&position2, 
		D3DCOLOR_ARGB(alpha2, 255, 255, 255));

	SpHd->Draw(
		menu_word_view, 
		NULL, 
		NULL, 
		&position3, 
		D3DCOLOR_ARGB(alpha3, 255, 255, 255));

	SpHd->Draw(
		menu_speed_change, 
		NULL, 
		NULL, 
		&position4, 
		D3DCOLOR_ARGB(alpha4, 255, 255, 255));

	SpHd->Draw(
		menu_mute_sounds, 
		NULL, 
		NULL, 
		&position5, 
		D3DCOLOR_ARGB(alpha5, 255, 255, 255));

	SpHd->Draw(
		menu_exit_menu, 
		NULL, 
		NULL, 
		&position6, 
		D3DCOLOR_ARGB(alpha6, 255, 255, 255));

	SpHd->Draw(
		menu_exit_game, 
		NULL, 
		NULL, 
		&position7, 
		D3DCOLOR_ARGB(alpha7, 255, 255, 255));
}

int Wait(int time)
{
	if (wait_count < time)
	{
		wait_count++;
	}

	if (wait_count == time)
	{
		wait_count = 0;
		return 1;
	}

	if (wait_count != time)
	{
		return 0;
	}
}

void Fade_Out()
{
	if (fade_speedc == 1)
	{
		fade_status = 2;
	}

	if (fade_status == 1 || fade_status == 2 || fade_status == 3)
	{
		fade_count++;
	}

	if (fade_count == 100)
	{
		fade_status = 2;

		D3DXVECTOR3 position ((float)0, (float)0, 0);

		SpHd->Draw(
			menu_fader, 
			NULL, 
			NULL, 
			&position, 
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if (fade_status == 1)
	{
		fade_alpha = fade_alpha + fade_ainc;

		if (fade_alpha >= 255)
		{
			fade_ainc = 0;
			fade_alpha = 255;
		}

		D3DXVECTOR3 position ((float)0, (float)0, 0);

		SpHd->Draw(
			menu_fader, 
			NULL, 
			NULL, 
			&position, 
			D3DCOLOR_ARGB(fade_alpha, 255, 255, 255));
	}

	if (fade_status == 2)
	{
		if (fade_vn == 1)
		{
			VN_status = 0;
			Snow.Reset();
			Forest.Reset();
			HUD_Reset();
			menu_status = 1;
			fade_vn = 0;
			words_active = 0;

			fade_status = 3;
		}

		if (fade_menu == 1)
		{
			menu_status = 0;
			VN_status = 1;
			HUD_status = 1;
			fade_alpha = 0;
			fade_status = 0;
			fade_ainc = 5;
			fade_adec = 5;
			fade_count = 0;
			fade_menu = 0;

			menu_pick = 1;

			Activate();

			VN_active = 1;

			return;
		}

		if (fade_menu_speedc == 1)
		{
			fade_alpha = 0;
			fade_status = 0;
			fade_ainc = 5;
			fade_adec = 5;
			fade_count = 0;
			fade_menu = 0;
			menu_status = 0;

			fade_menu_speedc = 0;

			speedc_status = 1;

			return;
		}

		if (fade_speedc == 1)
		{
			if (Wait(40) == 1)
			{
				VN_status = 1;
				HUD_status = 1;
				fade_alpha = 0;
				fade_status = 0;
				fade_ainc = 5;
				fade_adec = 5;
				fade_count = 0;
				fade_menu = 0;
				menu_pick = 1;

				VN_active = 1;

				Activate();

				fade_speedc = 0;
			}

			return;
		}

		if (fade_word_view == 1)
		{
			view_y = 0;
			view_slider_y = 0;
			view_status = 0;

			if (Wait(40) == 1)
			{
				VN_status = 1;
				HUD_status = 1;
				fade_alpha = 0;
				fade_status = 0;
				fade_ainc = 5;
				fade_adec = 5;
				fade_count = 0;
				fade_menu = 0;
				menu_pick = 1;

				Activate();

				VN_active = 1;
			}

			return;
		}

		if (fade_menu_view == 1)
		{
			menu_status = 0;

			if (Wait(40) == 1)
			{
				fade_status = 3;
				view_status = 1;
			}
		}
	}

	if (fade_status == 3)
	{
		fade_alpha = fade_alpha - fade_adec;

		D3DXVECTOR3 position ((float)0, (float)0, 0);

		SpHd->Draw(
			menu_fader, 
			NULL, 
			NULL, 
			&position, 
			D3DCOLOR_ARGB(fade_alpha, 255, 255, 255));

		if (fade_alpha <= 0)
		{
			fade_alpha = 0;
			fade_status = 0;
			fade_ainc = 5;
			fade_adec = 5;
			fade_count = 0;
		}

		if (menu_status == 1 && fade_alpha <= 0)
		{
			menu_active = 1;
		}

		if (fade_menu_view == 1 && fade_alpha <= 0)
		{
			fade_menu_view = 0;
			fade_status = 0;
			view_active = 1;
		}
	}
}

void Speed_Change()
{
	if (speedc_status == 1)
	{
		speedc_count++;
	}

	if (speedc_status == 1 && speedc_count == 60)
	{
		help_ainc = 3;
		
		help_string = "That blueberry was the sweetest one I've ever eaten!";
	}

	if (speedc_status == 1 && help_alpha >= 255)
	{
		help_ainc = 0;
		help_alpha = 255;
	}

	if (speedc_status == 1 && help_alpha <= 0)
	{
		help_adec = 0;
		help_alpha = 0;
	}

	if (speedc_alpha >= 255 && speedc_status == 1)
	{
		speedc_ainc = 0;
		speedc_alpha = 255;
	}

	if (speedc_alpha <= 0 && speedc_status == 1)
	{
		speedc_adec = 0;
		speedc_alpha = 0;
	}

	if (speedc_status == 1 && speedc_count == 130)
	{
		speedc_button_status = 0;
	}

	if (speedc_status == 1 && speedc_count == 180)
	{
		game_font_active = 1;
		game_font_status = 1;
	}

	if (speedc_status == 1 && speedc_count > 140 && help_counter < strlen(help_string))
	{
		if (speedc_pick == 1)
		{
			if (speedc_count % 7 == 0 && game_font_active == 1)
			{
				help_counter++;
			}
		}

		if (speedc_pick == 2)
		{
			if (speedc_count % 5 == 0 && game_font_active == 1)
			{
				help_counter++;
			}
		}

		if (speedc_pick == 3)
		{
			if (speedc_count % 4 == 0 && game_font_active == 1)
			{
				help_counter++;
			}
		}

		if (speedc_pick == 4)
		{
			if (speedc_count % 3 == 0 && game_font_active == 1)
			{
				help_counter++;
			}
		}

		if (speedc_pick == 5)
		{
			if (speedc_count % 2 == 0 && game_font_active == 1)
			{
				help_counter++;
			}
		}
	}

	if (speedc_status == 1 && game_font_status == 1 && game_font_alpha <= 0)
	{
		game_font_adec = 0;
		game_font_alpha = 0;
	}

	if (speedc_status == 1 && speedc_button_status == 1)
	{
		if (Key_Down(DIK_RIGHT) && speedc_pick != 5 && speedc_count_keeper + 12 < speedc_count)
		{
			speedc_pick++;
			speedc_count_keeper = speedc_count;
			help_counter = 0;
		}

		if (Key_Down(DIK_LEFT) && speedc_pick != 1 && speedc_count_keeper + 12 < speedc_count)
		{
			speedc_pick--;
			speedc_count_keeper = speedc_count;
			help_counter = 0;
		}
	}

	if (speedc_status == 1 && speedc_button_status == 1)
	{
		if (Key_Down(DIK_RETURN))
		{
				speed_input = speedc_pick;
				speedc_button_status = 2;
				help_adec = 5;
				speedc_adec = 3;
				game_font_active = 0;
				game_font_adec = 5;
		}
	}

	if (speedc_status == 1 && speedc_button_status == 1)
	{
		if (speedc_pick == 1)
		{
			Speed_Select_Sub(speedc_main_alpha, speedc_others_alpha, speedc_others_alpha, speedc_others_alpha, speedc_others_alpha);
		}
		
		if (speedc_pick == 2)
		{
			Speed_Select_Sub(speedc_others_alpha, speedc_main_alpha, speedc_others_alpha, speedc_others_alpha, speedc_others_alpha);
		}

		if (speedc_pick == 3)
		{
			Speed_Select_Sub(speedc_others_alpha, speedc_others_alpha, speedc_main_alpha, speedc_others_alpha, speedc_others_alpha);
		}

		if (speedc_pick == 4)
		{
			Speed_Select_Sub(speedc_others_alpha, speedc_others_alpha, speedc_others_alpha, speedc_main_alpha, speedc_others_alpha);
		}

		if (speedc_pick == 5)
		{
			Speed_Select_Sub(speedc_others_alpha, speedc_others_alpha, speedc_others_alpha, speedc_others_alpha, speedc_main_alpha);
		}
	}

	if (speedc_status == 1 && speedc_button_status == 0)
	{
		if (speedc_main_alpha < 255)
		{
			speedc_main_alpha = speedc_main_alpha + speedc_main_ainc;
		}

		if (speedc_main_alpha >= 255)
		{
			speedc_main_alpha = 255;
			speedc_main_ainc = 0;
		}

		if (speedc_main_alpha <= 0)
		{
			speedc_main_adec = 0;
			speedc_main_alpha = 0;
		}

		if (speedc_others_alpha < 120)
		{
			speedc_others_alpha = speedc_others_alpha + speedc_others_ainc;
		}

		Speed_Select_Sub(speedc_others_alpha, speedc_others_alpha, speedc_main_alpha, speedc_others_alpha, speedc_others_alpha);

		if (speedc_others_alpha == 120 && speedc_main_alpha == 255)
		{
			speedc_button_status = 1;
		}
	}

	if (speedc_status == 1 && speedc_button_status == 2)
	{
		if (speedc_pick == 1)
		{
			Speed_Select_Sub(speedc_main_alpha, speedc_others_alpha, speedc_others_alpha, speedc_others_alpha, speedc_others_alpha);
		}

		if (speedc_pick == 2)
		{
			Speed_Select_Sub(speedc_others_alpha, speedc_main_alpha, speedc_others_alpha, speedc_others_alpha, speedc_others_alpha);
		}

		if (speedc_pick == 3)
		{
			Speed_Select_Sub(speedc_others_alpha, speedc_others_alpha, speedc_main_alpha, speedc_others_alpha, speedc_others_alpha);
		}

		if (speedc_pick == 4)
		{
			Speed_Select_Sub(speedc_others_alpha, speedc_others_alpha, speedc_others_alpha, speedc_main_alpha, speedc_others_alpha);
		}

		if (speedc_pick == 5)
		{
			Speed_Select_Sub(speedc_others_alpha, speedc_others_alpha, speedc_others_alpha, speedc_others_alpha, speedc_main_alpha);
		}

		if (speedc_main_alpha > 0)
		{
			speedc_main_alpha = speedc_main_alpha - speedc_main_adec;
		}

		if (speedc_others_alpha > 0)
		{
			speedc_others_alpha = speedc_others_alpha - speedc_others_adec;
		}

		if (speedc_alpha > 0)
		{
			speedc_alpha = speedc_alpha - speedc_adec;
		}

		if (speedc_others_alpha == 0 && speedc_main_alpha == 0 && speedc_alpha == 0 && help_alpha == 0 && game_font_alpha == 0)
		{
			speedc_button_status = 3;
			game_font_status = 0;
		}
	}

	if (speedc_status == 1 && speedc_count >= 40)
	{
		RECT rect;
		rect.top = 150;
		rect.left = 0;
		rect.bottom = 500;
		rect.right = 800;

		speed_font->DrawText(
		NULL, 
		speedc_string, 
		-1, 
		&rect, 
		DT_CENTER, 
		D3DCOLOR_ARGB(speedc_alpha, 255, 255, 255));

		speedc_alpha = speedc_alpha + speedc_ainc;
	}


	if (speedc_status == 1 && speedc_count >= 140 && game_font_status == 1)
	{
		RECT rect;
		rect.top = 450;
		rect.left = 148;
		rect.bottom = 600;
		rect.right = 700;

		game_font->DrawText(
		NULL, 
		help_string, 
		help_counter, 
		&rect, 
		DT_LEFT, 
		D3DCOLOR_ARGB(game_font_alpha, 240, 240, 255));

		game_font_alpha = game_font_alpha - game_font_adec;
	}

	if (speedc_button_status == 3)
	{
		speedc_status = 0;
		help_alpha = 0;
		help_ainc = 0;
		help_adec = 0;
		help_counter = 0;

		fade_status = 1;
		fade_speedc = 1;

		speedc_status = 0;
		speedc_count = 0;
		speedc_count_keeper = 0;
		speedc_button_status = 10;
		speedc_alpha = 0;
		speedc_ainc = 3;
		speedc_adec = 0;
		speedc_main_alpha = 0;
		speedc_others_alpha = 0;
		speedc_main_ainc = 5;
		speedc_main_adec = 3;
		speedc_others_ainc = 3;
		speedc_others_adec = 5;
		speedc_pick = 3;

		game_font_alpha = 255;
		game_font_ainc = 0;
		game_font_adec = 0;
		game_font_active = 0;
		game_font_status = 0;
	}
}

void Activate()
{
	words_active = 1;
}

void View_Words()
{
	if (view_status == 1)
	{
		D3DXVECTOR3 position1 ((float)0, (float)0, 0);

		D3DXVECTOR3 position2 ((float)0, (float)0, 0);

		D3DXVECTOR3 position3 ((float)0, (float)0, 0);

		D3DXVECTOR3 position4 ((float)0, (float)0 + view_slider_y, 0);

		if (view_active == 1)
		{
				if (Key_Down(DIK_DOWN) && view_slider_y < 0)
				{
					view_slider_y = view_slider_y + 2;
					view_y = view_y - 5;
				}

				if (Key_Down(DIK_UP) && view_slider_y > -400)
				{
					view_slider_y = view_slider_y - 2;
					view_y = view_y + 5;
				}
		}

		RECT rect1;
		rect1.top = 395 + view_y;
		rect1.left = 35;
		rect1.bottom = 525 + view_y;
		rect1.right = 670;

		RECT rect2;
		rect2.top = 265 + view_y;
		rect2.left = 35;
		rect2.bottom = 395 + view_y;
		rect2.right = 670;

		RECT rect3;
		rect3.top = 135 + view_y;
		rect3.left = 35;
		rect3.bottom = 265 + view_y;
		rect3.right = 670;

		RECT rect4;
		rect4.top = 5 + view_y;
		rect4.left = 35;
		rect4.bottom = 135 + view_y;
		rect4.right = 670;

		RECT rect5;
		rect5.top = -125 + view_y;
		rect5.left = 35;
		rect5.bottom = 05 + view_y;
		rect5.right = 670;

		RECT rect6;
		rect6.top = -255 + view_y;
		rect6.left = 35;
		rect6.bottom = -125 + view_y;
		rect6.right = 670;

		RECT rect7;
		rect7.top = -385 + view_y;
		rect7.left = 35;
		rect7.bottom = -255 + view_y;
		rect7.right = 670;

		RECT rect8;
		rect8.top = -515 + view_y;
		rect8.left = 35;
		rect8.bottom = -385 + view_y;
		rect8.right = 670;

		RECT rect9;
		rect9.top = -645 + view_y;
		rect9.left = 35;
		rect9.bottom = -515 + view_y;
		rect9.right = 670;

		RECT rect10;
		rect10.top = -775 + view_y;
		rect10.left = 35;
		rect10.bottom = -645 + view_y;
		rect10.right = 670;

		RECT rect11;
		rect11.top = -905 + view_y;
		rect11.left = 35;
		rect11.bottom = -775 + view_y;
		rect11.right = 670;

		view_font->DrawText(
		SpHd, 
		s1, 
		-1, 
		&rect1, 
		DT_WORDBREAK,
		D3DCOLOR_XRGB(255, 255, 255));

		view_font->DrawText(
		SpHd, 
		s2, 
		-1, 
		&rect2, 
		DT_WORDBREAK,
		D3DCOLOR_XRGB(255, 255, 255));

		view_font->DrawText(
		SpHd, 
		s3, 
		-1, 
		&rect3, 
		DT_WORDBREAK,
		D3DCOLOR_XRGB(255, 255, 255));

		view_font->DrawText(
		SpHd, 
		s4, 
		-1, 
		&rect4, 
		DT_WORDBREAK,
		D3DCOLOR_XRGB(255, 255, 255));

		view_font->DrawText(
		SpHd, 
		s5, 
		-1, 
		&rect5, 
		DT_WORDBREAK,
		D3DCOLOR_XRGB(255, 255, 255));

		view_font->DrawText(
		SpHd, 
		s6, 
		-1, 
		&rect6, 
		DT_WORDBREAK,
		D3DCOLOR_XRGB(255, 255, 255));

		view_font->DrawText(
		SpHd, 
		s7, 
		-1, 
		&rect7, 
		DT_WORDBREAK,
		D3DCOLOR_XRGB(255, 255, 255));

		view_font->DrawText(
		SpHd, 
		s8, 
		-1, 
		&rect8, 
		DT_WORDBREAK,
		D3DCOLOR_XRGB(255, 255, 255));

		view_font->DrawText(
		SpHd, 
		s9, 
		-1, 
		&rect9, 
		DT_WORDBREAK,
		D3DCOLOR_XRGB(255, 255, 255));

		view_font->DrawText(
		SpHd, 
		s10, 
		-1, 
		&rect10, 
		DT_WORDBREAK,
		D3DCOLOR_XRGB(255, 255, 255));

		view_font->DrawText(
		SpHd, 
		s11, 
		-1, 
		&rect11, 
		DT_WORDBREAK,
		D3DCOLOR_XRGB(255, 255, 255));

		SpHd->Draw(
			view_blockers, 
			NULL, 
			NULL, 
			&position1, 
			D3DCOLOR_ARGB(255, 255, 255, 255));

		SpHd->Draw(
			view_bg, 
			NULL, 
			NULL, 
			&position1, 
			D3DCOLOR_ARGB(90, 255, 255, 255));

		if (Key_Down(DIK_UP) && view_slider_y > -400)
		{
			SpHd->Draw(
				view_arrow1, 
				NULL, 
				NULL, 
				&position2, 
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
		{
			SpHd->Draw(
				view_arrow1, 
				NULL, 
				NULL, 
				&position2, 
				D3DCOLOR_ARGB(170, 255, 255, 255));
		}

		if (Key_Down(DIK_DOWN) && view_slider_y < 0)
		{
			SpHd->Draw(
				view_arrow2, 
				NULL, 
				NULL, 
				&position3, 
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
		{
			SpHd->Draw(
				view_arrow2, 
				NULL, 
				NULL, 
				&position3, 
				D3DCOLOR_ARGB(170, 255, 255, 255));
		}

		SpHd->Draw(
			view_slider, 
			NULL, 
			NULL, 
			&position4, 
			D3DCOLOR_ARGB(170, 255, 255, 255));

		if (Key_Down(DIK_ESCAPE) && view_active == 1)
		{
			fade_status = 1;
			fade_word_view = 1;
			view_active = 0;
		}
	}
}

void Load_Words(char* str1,
				char* str2,
				char* str3,
				char* str4,
				char* str5,
				char* str6,
				char* str7,
				char* str8,
				char* str9,
				char* str10,
				char* str11)
{
	vs1 = str1;
	vs2 = str2;
	vs3 = str3;
	vs4 = str4;
	vs5 = str5;
	vs6 = str6;
	vs7 = str7;
	vs8 = str8;
	vs9 = str9;
	vs10 = str10;
	vs11 = str11;
}

void Visual_Novel()
{
	if (VN_status == 1)
	{
		if (phase == 0)
		{
			if (Wait(180) == 1)
			{
				phase = 1;
			}
		}

		if (phase == 1)
		{
			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s1, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 222;
				}
			}
		}

		if (phase == 222)
		{
			HUD_Display(1);

			if (HUD_done == 1)
			{
				int w;
				w = 0;

				w = Word_Processor(s222, "", speed_input, 255, 0, 255, 1);

				if (w == 1)
				{
					phase = 2;
				}

				if (w == 2)
				{
					phase = 223;
				}
			}
		}

		if (phase == 223)
		{
			if (HUD_done == 1)
			{
				if (Hamburger.Display(3, 0) == 1)
				{
					phase = 224;
				}
			}

			HUD_Display(1);
		}

		if (phase == 224)
		{
			if (HUD_done == 1)
			{
				Hamburger.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s224, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 225;
				}
			}
		}

		if (phase == 225)
		{
			if (HUD_done == 1)
			{
				Hamburger.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				int w;
				w = 0;

				w = Word_Processor(s225, "", speed_input, 255, 255, 255, 1);

				if (w == 1)
				{
					phase = 0;
					HUD_Reset();
				}
			}
		}

		if (phase == 2)
		{
			if (HUD_done == 1)
			{
				if (Boat.Display(3, 0) == 1)
				{
					phase = 3;
					Boat.Reload();
				}
			}

			HUD_Display(1);
		}

		if (phase == 3)
		{
			if (HUD_done == 1)
			{
				Boat.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s2, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 4;
				}
			}
		}

		if (phase == 4)
		{
			if (HUD_done == 1)
			{
				Boat.Display(3, 0);
				if (Map.Display(3, 0) == 1)
				{
					phase = 5;
				}
			}

			HUD_Display(1);
		}

		if (phase == 5)
		{
			if (HUD_done == 1)
			{
				Boat.Vanish(3, 0);
				Map.Display(3, 0);
			}

			HUD_Display(1);

			if (Word_Processor(s3, "", speed_input, 255, 255, 255, 0) == 1)
			{
				phase = 6;
			}
		}

		if (phase == 6)
		{
			if (HUD_done == 1)
			{
				Map.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s4, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 7;
				}
			}
		}

		if (phase == 7)
		{
			if (HUD_done == 1)
			{
				Map.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s5, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 333;
				}
			}
		}

		if (phase == 333)
		{
			if (HUD_done == 1)
			{
				Map.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				int w;
				w = 0;

				w = Word_Processor(s333, "", speed_input, 255, 0, 255, 1);

				if (w == 1)
				{
					phase = 334;
				}

				if (w == 2)
				{
					phase = 8;
				}
			}
		}

		if (phase == 334)
		{
			if (HUD_done == 1)
			{
				Map.Display(3, 0);
				if (Triton.Display(3, 0) == 1)
				{
					phase = 335;
				}
			}

			HUD_Display(1);
		}

		if (phase == 335)
		{
			if (HUD_done == 1)
			{
				Triton.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s334, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 336;
				}
			}
		}

		if (phase == 336)
		{
			if (HUD_done == 1)
			{
				Triton.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				int w;
				w = 0;

				w = Word_Processor(s335, "", speed_input, 255, 255, 255, 1);

				if (w == 1)
				{
					phase = 6;
					HUD_Reset();
				}
			}
		}

		if (phase == 8)
		{
			if (HUD_done == 1)
			{
				Map.Display(3, 0);
				if (Yale.Display(3, 0) == 1)
				{
					phase = 9;
				}
			}

			HUD_Display(1);
		}

		if (phase == 9)
		{
			if (HUD_done == 1)
			{
				Yale.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s6, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 10;
				}
			}
		}

		if (phase == 10)
		{
			if (HUD_done == 1)
			{
				Yale.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s7, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 11;
				}
			}
		}

		if (phase == 11)
		{
			if (HUD_done == 1)
			{
				Yale.Display(3, 0);
				if (Housein.Display(3, 0) == 1)
				{
					phase = 12;
				}
			}

			HUD_Display(1);
		}

		if (phase == 12)
		{
			if (HUD_done == 1)
			{
				Housein.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s8, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 13;
				}
			}
		}

		if (phase == 13)
		{
			if (HUD_done == 1)
			{
				Housein.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s9, "Tom", speed_input, 255, 255, 0, 0) == 1)
				{
					phase = 14;
				}
			}
		}

		if (phase == 14)
		{
			if (HUD_done == 1)
			{
				Housein.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s10, "Daisy", speed_input, 255, 255, 0, 0) == 1)
				{
					phase = 15;
				}
			}
		}

		if (phase == 15)
		{
			if (HUD_done == 1)
			{
				Housein.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s11, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 16;
				}
			}
		}

		if (phase == 16)
		{
			if (HUD_done == 1)
			{
				Housein.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s12, "Jordan", speed_input, 255, 255, 0, 0) == 1)
				{
					phase = 17;
				}
			}
		}

		if (phase == 17)
		{
			if (HUD_done == 1)
			{
				Housein.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s13, "You", speed_input, 255, 255, 0, 0) == 1)
				{
					phase = 18;
				}
			}
		}

		if (phase == 18)
		{
			if (HUD_done == 1)
			{
				Housein.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s14, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 19;
				}
			}
		}

		if (phase == 19)
		{
			if (HUD_done == 1)
			{
				Housein.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s15, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 20;
					Map.Reset();
					Map.Reload();
				}
			}
		}

		if (phase == 20)
		{
			if (HUD_done == 1)
			{
				Housein.Display(3, 0);
				if (Map.Display(3, 0) == 1)
				{
					phase = 21;
				}
			}

			HUD_Display(1);
		}

		if (phase == 21)
		{
			if (HUD_done == 1)
			{
				Map.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s16, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 22;
				}
			}
		}

		if (phase == 22)
		{
			if (HUD_done == 1)
			{
				Map.Display(3, 0);

				if (Eyes.Display(3, 0) == 1)
				{
					phase = 23;
				}
			}

			HUD_Display(1);
		}

		if (phase == 23)
		{
			if (HUD_done == 1)
			{
				Eyes.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s444, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 444;
				}
			}
		}

		if (phase == 444)
		{
			if (HUD_done == 1)
			{
				Eyes.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				int w;
				w = 0;

				w = Word_Processor(s444, "", speed_input, 255, 0, 255, 1);

				if (w == 1)
				{
					phase = 24;
				}

				if (w == 2)
				{
					phase = 24;
				}
			}
		}

		if (phase == 24)
		{
			if (HUD_done == 1)
			{
				Eyes.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s18, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 25;
				}
			}
		}

		if (phase == 25)
		{
			if (HUD_done == 1)
			{
				Eyes.Display(3, 0);
				if (Party.Display(3, 0) == 1)
				{
					phase = 26;
				}
			}

			HUD_Display(1);
		}

		if (phase == 26)
		{
			if (HUD_done == 1)
			{
				Party.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s19, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 27;
				}
			}
		}

		if (phase == 27)
		{
			if (HUD_done == 1)
			{
				Party.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s20, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 555;
				}
			}
		}

		if (phase == 555)
		{
			if (HUD_done == 1)
			{
				Party.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				int w;
				w = 0;

				w = Word_Processor(s555, "", speed_input, 255, 0, 255, 1);

				if (w == 1)
				{
					phase = 556;
				}

				if (w == 2)
				{
					phase = 28;
				}
			}
		}

		if (phase == 556)
		{
			if (HUD_done == 1)
			{
				Party.Display(3, 0);
				if (Anime.Display(3, 0) == 1)
				{
					phase = 557;
				}
			}

			HUD_Display(1);
		}

		if (phase == 557)
		{
			if (HUD_done == 1)
			{
				Anime.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s556, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 558;
				}
			}
		}

		if (phase == 558)
		{
			if (HUD_done == 1)
			{
				Anime.Display(3, 0);
				if (Apoc.Display(3, 0) == 1)
				{
					phase = 559;
				}
			}

			HUD_Display(1);
		}

		if (phase == 559)
		{
			if (HUD_done == 1)
			{
				Apoc.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s557, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 560;
				}
			}
		}

		if (phase == 560)
		{
			if (HUD_done == 1)
			{
				Apoc.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				int w;
				w = 0;

				w = Word_Processor(s558, "", speed_input, 255, 0, 255, 1);

				if (w == 1)
				{
					phase = 26;
					HUD_Reset();
				}
			}
		}

		if (phase == 28)
		{
			if (HUD_done == 1)
			{
				Party.Vanish(3, 0);
				if (Mansion.Display(3, 0) == 1)
				{
					phase = 29;
				}
			}

			HUD_Display(1);
		}

		if (phase == 29)
		{
			if (HUD_done == 1)
			{
				Mansion.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s21, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 30;
				}
			}
		}

		if (phase == 30)
		{
			if (HUD_done == 1)
			{
				Mansion.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s22, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 31;
				}
			}
		}

		if (phase == 31)
		{
			if (HUD_done == 1)
			{
				Mansion.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s23, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 32;
				}
			}
		}

		if (phase == 32)
		{
			if (HUD_done == 1)
			{
				Mansion.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s24, "Jay Gatsby", speed_input, 255, 255, 0, 0) == 1)
				{
					phase = 33;
				}
			}
		}

		if (phase == 33)
		{
			if (HUD_done == 1)
			{
				Mansion.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s25, "You", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 34;
				}
			}
		}

		if (phase == 34)
		{
			if (HUD_done == 1)
			{
				Mansion.Display(3, 0);
				if (Medal.Display(3, 0) == 1)
				{
					phase = 35;
				}
			}

			HUD_Display(1);
		}

		if (phase == 35)
		{
			if (HUD_done == 1)
			{
				Medal.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s26, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 36;
				}
			}
		}

		if (phase == 36)
		{
			if (HUD_done == 1)
			{
				Medal.Display(3, 0);
				if (Rest1.Display(3, 0) == 1)
				{
					phase = 37;
				}
			}

			HUD_Display(1);
		}

		if (phase == 37)
		{
			if (HUD_done == 1)
			{
				Rest1.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s27, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 38;
				}
			}
		}

		if (phase == 38)
		{
			if (HUD_done == 1)
			{
				Rest1.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s28, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 39;
				}
			}
		}

		if (phase == 39)
		{
			if (HUD_done == 1)
			{
				Rest1.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s29, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 40;
				}
			}
		}

		if (phase == 40)
		{
			if (HUD_done == 1)
			{
				Rest1.Display(3, 0);
				if(Rainy.Display(3, 0) == 1)
				{
					phase = 41;
				}
			}

			HUD_Display(1);
		}

		if (phase == 41)
		{
			if (HUD_done == 1)
			{
				Rainy.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s30, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 42;
				}
			}
		}

		if (phase == 42)
		{
			if (HUD_done == 1)
			{
				Rainy.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s31, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 43;
				}
			}
		}

		if (phase == 43)
		{
			if (HUD_done == 1)
			{
				Rainy.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s32, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 44;
				}
			}
		}

		if (phase == 44)
		{
			if (HUD_done == 1)
			{
				Rainy.Display(3, 0);
				if (Sunny.Display(3, 0) == 1)
				{
					phase = 45;
				}
			}

			HUD_Display(1);
		}

		if (phase == 45)
		{
			if (HUD_done == 1)
			{
				Sunny.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s33, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 46;
				}
			}
		}

		if (phase == 46)
		{
			if (HUD_done == 1)
			{
				Sunny.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s34, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 47;
				}
			}
		}

		if (phase == 47)
		{
			if (HUD_done == 1)
			{
				Sunny.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s35, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 48;
					Housein.Reload();
					Housein.Reset();
				}
			}
		}

		if (phase == 48)
		{
			if (HUD_done == 1)
			{
				Sunny.Display(3, 0);
				if (Housein.Display(3, 0) == 1)
				{
					phase = 49;
				}
			}

			HUD_Display(1);
		}

		if (phase == 49)
		{
			if (HUD_done == 1)
			{
				Housein.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s36, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 50;
				}
			}
		}

		if (phase == 50)
		{
			if (HUD_done == 1)
			{
				Housein.Display(3, 0);
				if (Balloons.Display(3, 0) == 1)
				{
					phase = 51;
				}
			}

			HUD_Display(1);
		}

		if (phase == 51)
		{
			if (HUD_done == 1)
			{
				Balloons.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s37, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 52;
				}
			}
		}

		if (phase == 52)
		{
			if (HUD_done == 1)
			{
				Balloons.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s38, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 53;
					Housein.Reload();
					Housein.Reset();
				}
			}
		}

		if (phase == 53)
		{
			if (HUD_done == 1)
			{
				Balloons.Display(3, 0);
				if (Housein.Display(3, 0) == 1)
				{
					phase = 54;
				}
			}

			HUD_Display(1);
		}

		if (phase == 54)
		{
			if (HUD_done == 1)
			{
				Housein.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s39, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 55;
				}
			}
		}

		if (phase == 55)
		{
			if (HUD_done == 1)
			{
				Housein.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s40, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 56;
				}
			}
		}

		if (phase == 56)
		{
			if (HUD_done == 1)
			{
				Housein.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s41, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 57;
				}
			}
		}

		if (phase == 57)
		{
			if (HUD_done == 1)
			{
				Housein.Display(3, 0);
				if (Hotel.Display(3, 0) == 1)
				{
					phase = 58;
				}
			}

			HUD_Display(1);
		}

		if (phase == 58)
		{
			if (HUD_done == 1)
			{
				Hotel.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s42, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 59;
				}
			}
		}

		if (phase == 59)
		{
			if (HUD_done == 1)
			{
				Hotel.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s43, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 60;
				}
			}
		}

		if (phase == 60)
		{
			if (HUD_done == 1)
			{
				Hotel.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s44, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 61;
				}
			}
		}

		if (phase == 61)
		{
			if (HUD_done == 1)
			{
				Hotel.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s45, "Jay Gatsby", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 62;
				}
			}
		}

		if (phase == 62)
		{
			if (HUD_done == 1)
			{
				Hotel.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s46, "You", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 63;
				}
			}
		}

		if (phase == 63)
		{
			if (HUD_done == 1)
			{
				Hotel.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s47, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 64;
					Mansion.Reload();
					Mansion.Reset();
				}
			}
		}

		if (phase == 64)
		{
			if (HUD_done == 1)
			{
				Hotel.Display(3, 0);

				if (Mansion.Display(3, 0) == 1)
				{
					phase = 65;
				}
			}

			HUD_Display(1);
		}

		if (phase == 65)
		{
			if (HUD_done == 1)
			{
				Mansion.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s48, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 66;
				}
			}
		}

		if (phase == 66)
		{
			if (HUD_done == 1)
			{
				Mansion.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s49, "Jay Gatsby", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 67;
				}
			}
		}

		if (phase == 67)
		{
			if (HUD_done == 1)
			{
				Mansion.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s50, "You", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 68;
				}
			}
		}

		if (phase == 68)
		{
			if (HUD_done == 1)
			{
				Mansion.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s51, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 69;
				}
			}
		}

		if (phase == 69)
		{
			if (HUD_done == 1)
			{
				Mansion.Display(3, 0);
				if (Loading.Display(3, 0) == 1)
				{
					phase = 70;
				}
			}

			HUD_Display(1);
		}

		if (phase == 70)
		{
			if (HUD_done == 1)
			{
				Loading.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s52, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 71;
				}
			}
		}

		if (phase == 71)
		{
			if (HUD_done == 1)
			{
				Loading.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s53, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 72;
				}
			}
		}

		if (phase == 72)
		{
			if (HUD_done == 1)
			{
				Loading.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s54, "You", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 73;
				}
			}
		}

		if (phase == 73)
		{
			if (HUD_done == 1)
			{
				Loading.Display(3, 0);
				if (Tombstone.Display(3, 0) == 1)
				{
					phase = 74;
				}
			}

			HUD_Display(1);
		}

		if (phase == 74)
		{
			if (HUD_done == 1)
			{
				Tombstone.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s55, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 75;
				}
			}
		}

		if (phase == 75)
		{
			if (HUD_done == 1)
			{
				Tombstone.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s56, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 76;
				}
			}
		}

		if (phase == 76)
		{
			if (HUD_done == 1)
			{
				Tombstone.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s57, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 77;
				}
			}
		}

		if (phase == 77)
		{
			if (HUD_done == 1)
			{
				Tombstone.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s58, "You", speed_input, 255, 255, 0, 0) == 1)
				{
					phase = 78;
				}
			}
		}

		if (phase == 78)
		{
			if (HUD_done == 1)
			{
				Tombstone.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s59, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 79;
				}
			}
		}

		if (phase == 79)
		{
			if (HUD_done == 1)
			{
				Tombstone.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s60, "You", speed_input, 255, 255, 0, 0) == 1)
				{
					phase = 80;
					Mansion.Reset();
					Mansion.Reload();
				}
			}
		}

		if (phase == 80)
		{
			if (HUD_done == 1)
			{
				Tombstone.Display(3, 0);
				if (Mansion.Display(3, 0) == 1)
				{
					phase = 81;
				}
			}

			HUD_Display(1);
		}

		if (phase == 81)
		{
			if (HUD_done == 1)
			{
				Mansion.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s61, "", speed_input, 255, 255, 255, 0) == 1)
				{
					phase = 82;
				}
			}
		}

		if (phase == 82)
		{
			if (HUD_done == 1)
			{
				Mansion.Display(3, 0);
			}

			HUD_Display(1);

			if (HUD_done == 1)
			{
				if (Word_Processor(s62, "You", speed_input, 255, 255, 0, 0) == 1)
				{
					phase = 83;
				}
			}
		}

		if (phase == 83)
		{
			if (HUD_done == 1)
			{
				Mansion.Display(3, 0);
				End.Display(1, 0);
			}

			HUD_Display(1);
		}
	}
}

void Game()
{
	Introduction();
	Title_Screen();
	Speed_Select();
	Name_Select();
	Visual_Novel();
}

void Game_Run(HWND hwnd)
{
	Poll_Mouse();
	Poll_Keyboard();

	if (d3ddev == NULL)
	{
		return;
	}

	if (d3ddev->BeginScene())
	{
		SpHd->Begin(D3DXSPRITE_ALPHABLEND);
		if ((GetTickCount() - 15)  >= start)
		{
			if (Key_Down(DIK_BACKSPACE))
			{
				PostMessage(hwnd, WM_DESTROY, 0, 0); 
			}
			start = GetTickCount();

			d3ddev->StretchRect(
				back, 
				NULL, 
				backbuffer, 
				NULL, 
				D3DTEXF_NONE);

			View_Words();

			if (speedc_status != 1 && view_status != 1)
			{
				Menu(hwnd);

				if (speedc_status != 1 && view_status != 1)
				{
					Game();
				}
			}

			Speed_Change();

			Fade_Out();
		}
		SpHd->End();
		d3ddev->EndScene();
	}

	
	if (Key_Down(DIK_DELETE))
	{
		PostMessage(hwnd, WM_DESTROY, 0, 0); 
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Game_End(HWND hwnd)
{
	if (SpHd != NULL)
	{
		SpHd->Release();
	}

	if (menu_box != NULL)
	{
		menu_box->Release();
	}

	if (menu_header != NULL)
	{
		menu_header->Release();
	}

	if (menu_word_view != NULL)
	{
		menu_word_view->Release();
	}

	if (menu_speed_change != NULL)
	{
		menu_speed_change->Release();
	}

	if (menu_mute_sounds != NULL)
	{
		menu_mute_sounds->Release();
	}

	if (menu_exit_menu != NULL)
	{
		menu_exit_menu->Release();
	}

	if (menu_exit_game != NULL)
	{
		menu_exit_game->Release();
	}

	if (menu_fader != NULL)
	{
		menu_fader->Release();
	}

	if (introduction != NULL)
	{
		introduction->Release();
	}

	if (back != NULL)
	{
		back->Release();
	}

	if (title != NULL)
	{
		title->Release();
	}

	if (arrow != NULL)
	{
		arrow->Release();
	}

	if (forest != NULL)
	{
		forest->Release();
	}

	if (HUD_out != NULL)
	{
		HUD_out->Release();
	}

	if (HUD_in != NULL)
	{
		HUD_in->Release();
	}

	if (view_arrow1 != NULL)
	{
		view_arrow1->Release();
	}

	if (view_arrow2 != NULL)
	{
		view_arrow2->Release();
	}

	if (view_bg != NULL)
	{
		view_bg->Release();
	}

	if (view_slider != NULL)
	{
		view_slider->Release();
	}

	if (view_blockers != NULL)
	{
		view_blockers->Release();
	}

	if (game_font != NULL)
	{
		game_font->Release();
	}

	if (title_font != NULL)
	{
		title_font->Release();
	}

	if (speed_font != NULL)
	{
		speed_font->Release();
	}

	if (speed_select_font != NULL)
	{
		speed_select_font->Release();
	}

	if (name_font != NULL)
	{
		name_font->Release();
	}

	if (name_select_font != NULL)
	{
		name_select_font->Release();
	}

	if (help_font != NULL)
	{
		help_font->Release();
	}

	if (view_font != NULL)
	{
		view_font->Release();
	}

	if (anime != NULL)
	{
		anime->Release();
	}
	
	if (ct != NULL)
	{
		ct->Release();
	}
	
	if (eend != NULL)
	{
		eend->Release();
	}
	
	if (hamburger != NULL)
	{
		hamburger->Release();
	}
	
	if (koala1 != NULL)
	{
		koala1->Release();
	}
	
	if (koala2 != NULL)
	{
		koala2->Release();
	}
	
	if (apoc != NULL)
	{
		apoc->Release();
	}
	
	if (triton != NULL)
	{
		triton->Release();
	}
	
	if (ufo != NULL)
	{
		ufo->Release();
	}
	
	if (balloons != NULL)
	{
		balloons->Release();
	}
	
	if (boat != NULL)
	{
		boat->Release();
	}
	
	if (eyes != NULL)
	{
		eyes->Release();
	}
	
	if (heart != NULL)
	{
		heart->Release();
	}
	
	if (hotel != NULL)
	{
		hotel->Release();
	}
	
	if (housein != NULL)
	{
		housein->Release();
	}
	
	if (loading != NULL)
	{
		loading->Release();
	}
	
	if (mansion != NULL)
	{
		mansion->Release();
	}
	
	if (map != NULL)
	{
		map->Release();
	}
	
	if (medal != NULL)
	{
		medal->Release();
	}
	
	if (party != NULL)
	{
		party->Release();
	}
	
	if (rest1 != NULL)
	{
		rest1->Release();
	}
	
	if (rest2 != NULL)
	{
		rest2->Release();
	}
	
	if (sunny != NULL)
	{
		sunny->Release();
	}
	
	if (rainy != NULL)
	{
		rainy->Release();
	}
	
	if (tombstone != NULL)
	{
		tombstone->Release();
	}
	
	if (yale != NULL)
	{
		yale->Release();
	}
}