#pragma once

b2Vec2 px_to_mt_pos(cocos2d::CCPoint &px_pos);
cocos2d::CCPoint mt_to_px_pos(const b2Vec2 &mt_pos);

float px_to_mt_length(float px_length);
float mt_to_px_length(float mt_length);