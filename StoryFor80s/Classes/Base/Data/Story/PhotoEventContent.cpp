//
//  PhotoEventContent.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#include "PhotoEventContent.hpp"
#include "JsonUtil.hpp"
#include "BaseScene.hpp"
#include "SceneManager.hpp"
#include "BaseLabel.hpp"
#include "DataManager.hpp"

#include <unordered_map>

cocos2d::Vec2 getScale(Node* child, Node *parent, PhotoScaleMode mode)
{
  switch (mode) {
    case PhotoScaleAspectFit: {
      auto scale = fmin(parent->getContentSize().width / child->getContentSize().width,
                        parent->getContentSize().height / child->getContentSize().height);
      return Vec2(scale, scale);
      break;
    }
    case PhotoScaleAspectFill: {
      auto scale = fmax(parent->getContentSize().width / child->getContentSize().width,
                        parent->getContentSize().height / child->getContentSize().height);
      return Vec2(scale, scale);
      break;
    }
    case PhotoScaleScaleFill: {
      return Vec2(parent->getContentSize().width / child->getContentSize().width,
                      parent->getContentSize().height / child->getContentSize().height);
      break;
    }
    default:
      break;
  }
  return Vec2(1, 1);
}

string PhotoEventContent::getMoveKey() const
{
  return p_name;
}

PhotoEventContent::PhotoEventContent(const nlohmann::json &jsonContent) : StoryEventContent(jsonContent)
{
  p_path = Utils::getStringFromJson(jsonContent, "path");
  p_name = Utils::getStringFromJson(jsonContent, "name");
  if (jsonContent.count("text")) {
    p_textInfo = Utils::getTextInfoFromJson(jsonContent, "text");
  }
  auto action = Utils::getStringFromJson(jsonContent, "action");
  static const unordered_map<string, PhotoEventAction> actionMap = {
    {"add", PhotoEventActionAdd},
    {"remove", PhotoEventActionRemove},
    {"move", PhotoEventActionMove}
  };
  CCASSERT(actionMap.count(action), "unknown music story action");
  p_action = actionMap.at(action);
  p_duration = Utils::getFloatFromJson(jsonContent, "duration");
  p_normalizePosition = Utils::getVec2FromJson(jsonContent, "normalized_position");
  p_anchorPoint = Utils::getVec2FromJson(jsonContent, "anchor_point");

  static const unordered_map<string, PhotoScaleMode> scaleMap = {
    {"aspect_fit", PhotoScaleAspectFit},
    {"aspect_fill", PhotoScaleAspectFill},
    {"scale_fill", PhotoScaleScaleFill}
  };
  auto scale = Utils::getStringFromJson(jsonContent, "scale");
  p_scaleMode = scaleMap.count(scale) ? scaleMap.at(scale) : PhotoScaleNone;
  p_opacity = Utils::getIntFromJson(jsonContent, "opacity");
  p_order = Utils::getIntFromJson(jsonContent, "order");
}

void PhotoEventContent::runEvent(StoryEventCallback callback)
{
  auto baseScene = SceneManager::getShareInstance()->currentScene();
  switch (p_action) {
    case PhotoEventActionAdd: {
      Node *photo = nullptr;
      if (p_path.length() > 0) {
        photo = Sprite::create(p_path);
      } else if (p_textInfo.text.length() > 0) {
        auto text = DataManager::getShareInstance()->decipherString(p_textInfo.text);
        auto label = BaseLabel::createWithSystemFont(text, "Helvetica", p_textInfo.size , p_textInfo.typingSpeed);
        label->setTypingEffect(p_textInfo.typingEffect);
        photo = label;
      }
      if (photo != nullptr) {
        photo->setName(p_name);
        photo->setAnchorPoint(p_anchorPoint);
        photo->setNormalizedPosition(p_normalizePosition);
        auto scaleVec = getScale(photo, baseScene, p_scaleMode);
        photo->setScale(scaleVec.x, scaleVec.y);
        baseScene->setOpacity(p_opacity);
        baseScene->addStoryPicture(photo, p_order);
      }
      break;
    }
    case PhotoEventActionRemove: {
      baseScene->removeStoryPicture(p_name);
      break;
    }
    case PhotoEventActionMove: {
      auto photo = baseScene->getStoryPictureByName(p_name);
      p_currentDuration = 0;
      if (photo != nullptr) {
        p_originNormalizePosition = photo->getNormalizedPosition();
        p_originAnchorPoint = photo->getAnchorPoint();
        p_originScaleX = photo->getScaleX();
        p_originScaleY = photo->getScaleY();
        p_originOpacity = photo->getOpacity();
        baseScene->schedule([this](float delta) {
          this->photoMoveTick(delta);
        }, getMoveKey());
      } else {
        CCLOGWARN("coudn't find photo by name :%s", p_name.c_str());
      }
      break;
    }
  }
  callback();
}


void PhotoEventContent::photoMoveTick(float delta)
{
  p_currentDuration += delta;
  auto baseScene = SceneManager::getShareInstance()->currentScene();
  auto photo = baseScene->getStoryPictureByName(p_name);
  if (photo == nullptr) {
    CCLOGWARN("couldn't find photo : %s, end photo move", p_name.c_str());
    baseScene->unschedule(getMoveKey());
    return;
  }
  if (p_currentDuration >= p_duration) {
    CCLOG("Photo (%s) move ended", p_name.c_str());
    baseScene->unschedule(getMoveKey());
    p_currentDuration = p_duration;
  }
  auto f = p_currentDuration / p_duration;
  if (p_opacity != p_originOpacity) {
    auto opacity = p_originOpacity + (p_opacity - p_opacity) * f;
    photo->setOpacity(opacity);
  }
  if (p_normalizePosition.x != p_originNormalizePosition.x || p_normalizePosition.y != p_originNormalizePosition.y) {
    auto normalizedX = p_originNormalizePosition.x + (p_normalizePosition.x - p_originNormalizePosition.x) * f;
    auto normalizedY = p_originNormalizePosition.y + (p_normalizePosition.y - p_originNormalizePosition.y) * f;
    photo->setNormalizedPosition(Vec2(normalizedX, normalizedY));
  }
  if (p_anchorPoint.x != p_originAnchorPoint.x || p_anchorPoint.y != p_originAnchorPoint.y) {
    auto anchorX = p_originAnchorPoint.x + (p_anchorPoint.x - p_originAnchorPoint.x) * f;
    auto anchorY = p_originAnchorPoint.y + (p_anchorPoint.y - p_originAnchorPoint.y) * f;
    photo->setAnchorPoint(Vec2(anchorX, anchorY));
  }
  auto scaleVec = getScale(photo, baseScene, p_scaleMode);
  if (scaleVec.x != p_originScaleX || scaleVec.y != p_originScaleY) {
    auto anchorX = p_originScaleX + (scaleVec.x - p_originScaleX) * f;
    auto anchorY = p_originScaleY + (scaleVec.y - p_originScaleY) * f;
    photo->setScale(anchorX, anchorY);
  }
}
