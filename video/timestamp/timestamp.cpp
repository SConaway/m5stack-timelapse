// #include <stdio.h>
// #include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>

#include <Magick++.h>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;
using namespace Magick;
// using

string parseName(string inName)
{
    auto dt = boost::gregorian::date_from_iso_string(inName.substr(0, 22));

    // format to MM/DD/YYYY HH:MM:SS
    // auto s = boost::gregorian::to_iso_extended_string(dt);
    // cout << s << endl;

    return "";
}

// string parseName(string inName)
// {
//     // 2022-12-23T21:54:22.706Z-camera.jpg

//     int year;
//     int month;
//     int day;
//     int hour;
//     int minute;
//     int second;

//     sscanf(inName.c_str(), "%d-%d-%dT%d:%d:%d.musZ-camera.jpg", &year, &month, &day, &hour, &minute, &second);

//     // create time object

//     struct tm timeinfo;
//     timeinfo.tm_year = year - 1900;
//     timeinfo.tm_mon = month - 1;
//     timeinfo.tm_mday = day;
//     timeinfo.tm_hour = hour;
//     timeinfo.tm_min = minute;
//     timeinfo.tm_sec = second;

//     time_t t = mktime(&timeinfo);

//     // convert from to America/Boise
//     // if (t.tm_isdst == 1)
//     // {
//     //     t -= 6 * 3600;
//     // }
//     // else
//     // {
//     t -= 7 * 3600;
//     // }

//     // convert to string
//     char buffer[80];
//     strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&t));

//     cout << buffer << endl;

//     return "";
// }

void processImage(string inName, string outName)
{
    // print name
    cout << "Processing " << inName << endl;

    // read image
    Image image;
    image.read(inName);
    // cout << "Image size: " << image.columns() << "x" << image.rows() << endl;

    // annotate
    // image.annotate("Hello World!", SouthEastGravity);

    // add text
    // list<Drawable> text_draw_list;
    vector<Drawable> text_draw_list;
    // set the text font: the font is specified via a string representing
    // a fully qualified X font name (wildcards '*' are allowed)
    // text_draw_list.push_back(
    //     DrawableFont("-misc-fixed-medium-o-semicondensed—13-*-*-*-c-60-iso8859-1"));
    text_draw_list.push_back(DrawableFont("Arial", NormalStyle, 0, NormalStretch));
    // set the text size
    text_draw_list.push_back(DrawablePointSize(32));
    // set the text to be drawn at specified position: x=101, y=50 this case
    text_draw_list.push_back(DrawableText(image.columns() - 260, image.rows() - 40, "text to write on the canvas"));
    // set the text color (the fill color must be set to transparent)
    text_draw_list.push_back(DrawableStrokeColor("white"));
    // text_draw_list.push_back(DrawableStrokeWidth(5)); // Stroke width
    text_draw_list.push_back(DrawableFillColor("white"));
    // draw the "text to write on the canvas" string on the canvas with the above settings
    image.draw(text_draw_list);

    // Construct drawing list
    // vector<Magick::Drawable> drawList;

    // Add some drawing options to drawing list
    // drawList.push_back(DrawableStrokeColor("black"));     // Outline color
    // drawList.push_back(DrawableStrokeWidth(5));           // Stroke width
    // drawList.push_back(DrawableFillColor("transparent")); // Fill color

    // // Add a Circle to drawing list
    // drawList.push_back(DrawableCircle(100, 100, 50, 100));

    // // Draw everything using completed drawing list
    // image.draw(drawList);

    // save as new image
    image.write(outName);
}

int main(int argc, char **argv)
{

    InitializeMagick(*argv);
    // printf("Hello World!\n");

    // processImage("2022-12-23T21:54:22.706Z-camera.jpg", "out.jpg");

    cout << parseName("2022-12-23T21:54:22.706Z-camera.jpg") << endl; // 12/23/2022 14:54
    cout << "should be 12/23/2022 14:54" << endl;
    cout << parseName("2022-12-27T04:36:40.397Z-camera.jpg") << endl; // 12/26/2022 21:36
    cout << "should be 12/26/2022 21:36" << endl;

    return 0;
}
