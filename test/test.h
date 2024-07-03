
    int bsum = (int)thisPixel.b + (int)otherPixel.b
            if (bsum > 255) {
                bsum = 255;
            }
            if (bsum < 0) {
                bsum = 0;
            }
            thisPixel.b = (unsigned char)bsum; 