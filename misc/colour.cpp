//source Ledrew, Glenn (February 2001). "The Real Starry Sky". Journal of the Royal Astronomical Society of Canada. 95: 32
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);

uint32_t property_assign(){
	//source: http://www.vendian.org/mncharity/dir3/starcolor/
	//O,B,A,F,G,K,M,R types
	uint32_t colors[] ={0x9bb0ffff,
						0xaabfffff,
				 		0xcad7ffff,
						0xf8f7ffff,
						0xfff4eaff,
						0xffd2a1ff,
						0xffcc6fff,

						0xff0000ff
	};
	//source: Ledrew, Glenn (February 2001). "The Real Starry Sky". Journal of the Royal Astronomical Society of Canada. 95: 32
	//O,B,A,F,G,K,M,R types
	double prob[] ={0.0000003,
					0.0013,
					0.006,
					0.03,
					0.076,
					0.121,
					0.7645,

					0.0011997
	};

	double rand = dis(gen);
	std::cout << rand << std::endl;
	double sum=0;
	int pick;
	for(int i = 0; i<8; i++){
		sum+=prob[i];
		std::cout << sum << std::endl;
		if(rand<=sum){
			std::cout << i << std::endl;
			pick=i;
			break;
		}
	}

	return colors[pick];

}

int main(){
	std::cout << std::hex << property_assign() << "\n";
}