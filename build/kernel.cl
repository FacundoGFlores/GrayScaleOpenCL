__kernel void gray_scale(__read_only image2d_t srcImg,
                              __write_only image2d_t dstImg,
                              sampler_t sampler,
                              int width, int height)
{

    int2 coords = (int2)(get_global_id(0), get_global_id(1));

    float4 pixel = read_imagef(srcImg, sampler, coords);

    float4 outColor = (pixel.x + pixel.y + pixel.z ) / 3;

    if(coords.x < width && coords.y < height)
      write_imagef(dstImg, coords, outColor);
}