#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>

using namespace sf;
using namespace std;


int main()
{
    // Create the main window

    Image img;
    string imgname;
    ifstream file("grayScale.txt");
    int skipi=1,skipj=1;
    string scale;

    cout<<"Enter image name : ";
    cin>>imgname;
    cout<<"Enter ratio of Vertical block : ";
    cin>>skipi;
    cout<<"Enter ratio of Horizontal block : ";
    cin>>skipj;
    getline(file,scale);
    freopen("out.txt","w",stdout);

    sf::RenderWindow app(sf::VideoMode(800, 600), "IMG to ASCII");

    img.loadFromFile(imgname);
    int height  = img.getSize().x;
    int width = img.getSize().y;

    for(int j=0;j<width;j+=skipj)
    {
        cout<<"//";
        for(int i=0;i<height;i+=skipi)
        {
            int avg=0,cnt=0;
            for(int nwj=0;nwj<skipj && j+nwj<width;nwj++)
            {
                for(int nwi=0;nwi<skipi && i+nwi<height;nwi++)
                {
                    Color c=img.getPixel(i+nwi,j+nwj);
                    int mx=max({c.r,c.g,c.b});
                    int mn=max({c.r,c.g,c.b});
                    avg+=(mn+mx)/2;
                    cnt++;
                }
            }
            avg/=cnt;
            int idx = scale.size()*avg/255;
            cout<<scale[idx];
        }
        cout<<"\n";
    }
    Texture texture;
    texture.loadFromImage(img);
    Sprite sprite(texture);

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear screen
        app.clear();

        app.draw(sprite);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
