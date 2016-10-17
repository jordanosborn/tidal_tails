#include <cmath>
#include <iostream>
void T_to_RGBA(double T, int (&rgb)[4],int alpha=255){
    double factor,wavelength;
    double b = 2.8977729 * 1000*1000; //in nm K
    if (T!=0){
        wavelength = b/std::abs(T);
    }
    else{
        wavelength = 800;
    }
    std::cout << wavelength <<std::endl;
    
    double R,G,B;
    double GAMMA = 0.80;
    double I_MAX = 255;

    if((wavelength >= 380) && (wavelength<440)){
        R = -(wavelength - 440) / (440 - 380);
        G = 0.0;
        B = 1.0;
    }
    else if((wavelength >= 440) && (wavelength<490)){
        R = 0.0;
        G = (wavelength - 440) / (490 - 440);
        B = 1.0;
    }
    else if((wavelength >= 490) && (wavelength<510)){
        R = 0.0;
        G = 1.0;
        B = -(wavelength - 510) / (510 - 490);
    }
    else if((wavelength >= 510) && (wavelength<580)){
        R = (wavelength - 510) / (580 - 510);
        G = 1.0;
        B = 0.0;
    }
    else if((wavelength >= 580) && (wavelength<645)){
        R = 1.0;
        G = -(wavelength - 645) / (645 - 580);
        B = 0.0;
    }
    else if((wavelength >= 645) && (wavelength<781)){
        R = 1.0;
        G = 0.0;
        B = 0.0;

    }
    //???????
    else if((wavelength>=781)){
        R=1.0;
        G=0.0;
        B=0.0;
    }
    //?????
    else if((wavelength<380)){
        R=1.0;
        G=1.0;
        B=1.0;
    }
    else{
        R = 0.0;
        G = 0.0;
        B = 0.0;
    };

    // Let the intensity fall off near the vision limits

    if((wavelength >= 380) && (wavelength<420)){
        factor = 0.3 + 0.7*(wavelength - 380) / (420 - 380);
    }else if((wavelength >= 420) && (wavelength<701)){
        factor = 1.0;
    }else if((wavelength >= 701) && (wavelength<781)){
        factor = 0.3 + 0.7*(780 - wavelength) / (780 - 700);
    }
    //???????
    else if((wavelength>=781)){
        factor=1.0;
    }
    //??????
    else if((wavelength<380)){
        factor=1.0;
    }
    else{
        factor = 0.0;
    };

    // Don't want 0^x = 1 for x <> 0
    rgb[0] = R==0.0 ? 0 : (int) std::round(I_MAX * std::pow(R * factor, GAMMA));
    rgb[1] = G==0.0 ? 0 : (int) std::round(I_MAX * std::pow(G * factor, GAMMA));
    rgb[2] = B==0.0 ? 0 : (int) std::round(I_MAX * std::pow(B * factor, GAMMA));
    rgb[3] = alpha;
}

//source http://www.efg2.com/Lab/ScienceAndEngineering/Spectra.htm

int main(){
    int rgb[4];
    T_to_RGBA(4900,rgb);
    std::cout << rgb[0] << " " << rgb[1] << " " << rgb[2]<< " " << rgb[3] << "\n";
    return 0;
}