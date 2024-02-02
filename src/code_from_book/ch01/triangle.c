
int triangle (int width, int height)
{
    int array[5] = {0,1,2,3,4};
    int area;
    area = width * height/2;
    return (area);
}

int main()
{
    int value = triangle (2, 3);
    return 0;
}