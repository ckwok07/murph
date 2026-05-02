
#version 330 core

in vec2 vUV;
out vec4 FragColor;

uniform vec3 uCameraPos;
uniform vec3 uCameraFront;
uniform vec3 uCameraRight;
uniform vec3 uCameraUp;

uniform vec3 uBlackHolePosition;
uniform float uEventHorizonRadius;
uniform float uTime;

uniform float uDiskInnerRadius;
uniform float uDiskOuterRadius;

void main() {
    vec2 uv = vUV * 2.0 - 1.0;
    vec3 dir = normalize(
        uCameraFront +
        uv.x * uCameraRight +
        uv.y * uCameraUp
    );

    vec3 pos = uCameraPos - uBlackHolePosition;
    float r = length(pos);
    float theta = acos(clamp(pos.y / r, -1.0, 1.0));
    float phi = atan(pos.z, pos.x);

    float dx = dir.x, dy = dir.y, dz = dir.z;
    float sinT = sin(theta), cosT = cos(theta);
    float sinP = sin(phi),   cosP = cos(phi);

    float dr     =  sinT*cosP*dx + cosT*dy      + sinT*sinP*dz;
    float dtheta = (cosT*cosP*dx - sinT*dy      + cosT*sinP*dz) / r;
    float dphi   = (-sinP*dx                    + cosP*dz)      / (r * sinT);

    float rs = uEventHorizonRadius;
    float f  = 1.0 - rs / r;
    float E  = f * sqrt(max((dr*dr)/f + r*r*(dtheta*dtheta + sin(theta)*sin(theta)*dphi*dphi), 0.0));

    bool hitBlackHole = false;
    bool hitDisk      = false;
    vec3 diskColor    = vec3(0.0);
    vec3 prevPos      = pos;

    float dL    = 0.01;
    int   steps = 10000;
    float startR = r;

    for (int i = 0; i < steps; i++) {
        if (r <= rs) { hitBlackHole = true; break; }
        if (r > startR * 3.0) break;

        sinT = sin(theta);
        cosT = cos(theta);
        float f2     = 1.0 - rs / r;
        float dt_dL  = E / f2;

        float d2r     = -(rs / (2.0*r*r)) * f2 * dt_dL*dt_dL
                    + (rs / (2.0*r*r*f2)) * dr*dr
                    + r * (dtheta*dtheta + sinT*sinT*dphi*dphi);
        float d2theta = -2.0*dr*dtheta/r + sinT*cosT*dphi*dphi;
        float d2phi   = -2.0*dr*dphi/r - 2.0*(cosT/max(sinT,0.001))*dtheta*dphi;

        dr     += dL * d2r;
        dtheta += dL * d2theta;
        dphi   += dL * d2phi;
        r      += dL * dr;
        theta  += dL * dtheta;
        phi    += dL * dphi;

        vec3 newPos = vec3(
            r * sin(theta) * cos(phi),
            r * cos(theta),
            r * sin(theta) * sin(phi)
        );

        if (prevPos.y * newPos.y < 0.0) {
            float diskDist = length(vec2(newPos.x, newPos.z));
            if (diskDist > uDiskInnerRadius && diskDist < uDiskOuterRadius) {
                float t = (diskDist - uDiskInnerRadius) / (uDiskOuterRadius - uDiskInnerRadius);

                vec3 diskPoint = newPos;
                vec3 radial = normalize(vec3(diskPoint.x, 0.0, diskPoint.z));
                vec3 orbitalDir = normalize(vec3(radial.z, 0.0, -radial.x));

                vec3 toCam = normalize(uCameraPos - (diskPoint + uBlackHolePosition));

                float doppler = 1.0 + dot(orbitalDir, toCam);
                doppler = pow(max(doppler, 0.0), 4.0);

                float intensity = clamp((1.0 - t) * 0.9, 0.0, 1.0) * doppler;
                diskColor = mix(vec3(1.0, 0.9, 0.4), vec3(1.0, 0.2, 0.0), t) * intensity;
                hitDisk       = true;
                break;
            }
        }

        prevPos = newPos;
    }

    if (hitBlackHole) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else if (hitDisk) {
        FragColor = vec4(diskColor, 1.0);
    } else {
        vec3 finalDir = vec3(
            sin(theta) * cos(phi),
            cos(theta),
            sin(theta) * sin(phi)
        );
        float stars = 0.0;
        vec3  q     = floor(finalDir * 150.0);
        float h     = fract(sin(dot(q, vec3(127.1, 311.7, 74.7))) * 43758.5453);
        if (h > 0.98) stars = h;
        FragColor = vec4(vec3(stars), 1.0);
    }
}